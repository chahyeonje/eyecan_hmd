#include <cstdio>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include <utility>
#include <vector>
#include <iostream>

#include "include/hmdgps.h"
#include "include/geomagnetic.h"
#include "include/switch.h"
#include "include/network.h"
#include "include/hmdcurl.h"
#include "include/speaker.h"
#include "include/camera.h"

#include "tensorflow/cc/ops/const_op.h"
#include "tensorflow/cc/ops/image_ops.h"
#include "tensorflow/cc/ops/standard_ops.h"
#include "tensorflow/core/framework/graph.pb.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/graph/default_device.h"
#include "tensorflow/core/graph/graph_def_builder.h"
#include "tensorflow/core/lib/core/errors.h"
#include "tensorflow/core/lib/core/stringpiece.h"
#include "tensorflow/core/lib/core/threadpool.h"
#include "tensorflow/core/lib/io/path.h"
#include "tensorflow/core/lib/strings/str_util.h"
#include "tensorflow/core/lib/strings/stringprintf.h"
#include "tensorflow/core/platform/env.h"
#include "tensorflow/core/platform/init_main.h"
#include "tensorflow/core/platform/logging.h"
#include "tensorflow/core/platform/types.h"
#include "tensorflow/core/public/session.h"
#include "tensorflow/core/util/command_line_flags.h"




// 쓰레드 함수
void *subTask1(void *data)
{
    while(1)
    {
        //스위치값 업데이트
        updateSwitch();
        
        //GPS 업데이트
        //updateGPS();라즈베리파이에서만 실행되는 함수
        
        //배터리검사
        //updateBattery();함수구현아직안됨
        
        //지자기 업데이트
        updateGeo();
        
        //서버에 센서값 전송
        sendData();
        
        sleep(1);
    }
}

void *subTask2(void *data)
{
    while(1)
    {
        
        bool bufferEmpty = isBufferEmpty();
        //버퍼가 비어있지 않을 때만
        if(!bufferEmpty)
        {
            //버퍼에 있는 값 TTS 재생
            playTTS("버퍼 데이터");
            //버퍼비우기
            flushBuffer();
        }
        sleep(1);
    }
}

void *speakerTask(void *data)
{
    while(1)
    {
        //스피커가 사용 중이지 않을 때에만 주기적으로 비프음 재생
        
        bool speakerBusy = s_busy;
        if(!speakerBusy)
        {
            
            //sleep! 여기서 적당히 쉬기, speaker.cc에 있는 bpm값을 이용해 쉬는 길이를 계산한다
            //score가 너무 낮으면 그냥 지나가야한다(너무 오래 기다리면 안됨)
            sleep(1);
            //score가 일정점수 이상일때만 playBeep()를 수행한다.
            speakerBusy = true;
            playBeep();
            
            speakerBusy = false;
        }
        
        
    }
}


void initDevice()
{
    //디바이스초기화 함수 부르기
    printf("Device Initialization...\n");
    initCamera();
    initGeo();
    initNetwork();
    //initGPS(); //라즈베리파이에서만 동작
    
    
}

int main()
{


    initDevice();//디바이스 초기화
    pthread_t p_thread[3];
    int thr_id;
    int status;
    int argTask1 = 1;//쓰레드로 넘길 아규먼트
    int argTask2 = 2;
    int argTask3 = 3;
    
    // 쓰레드 생성1
    thr_id = pthread_create(&p_thread[0], NULL, subTask1, (void *)&argTask1);
    if (thr_id < 0)
    {
        perror("thread create error : ");
        exit(0);
    }
    
    // 쓰레드 생성2
    thr_id = pthread_create(&p_thread[1], NULL, subTask2, (void *)&argTask2);
    if (thr_id < 0)
    {
        perror("thread create error : ");
        exit(0);
    }
    // 쓰레드 생성3
    thr_id = pthread_create(&p_thread[2], NULL, speakerTask, (void *)&argTask3);
    if (thr_id < 0)
    {
        perror("thread create error : ");
        exit(0);
    }
    
    while(1)
    {
        //스위치 상태 읽어오기
        bool segmentationOn = true;
        if(segmentationOn)
        {
            //픽셀값 업데이트
            updatePixel();
            getSegmentation();
            sleep(1);
            calculateScore();
        }
    }
    
    
    
    // 쓰레드 종료를 기다린다.
    pthread_join(p_thread[0], (void **)&status);
    pthread_join(p_thread[1], (void **)&status);
    pthread_join(p_thread[2], (void **)&status);
    
    return 0;
}
