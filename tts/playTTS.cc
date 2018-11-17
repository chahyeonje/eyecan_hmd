#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
bool s_busy=false; //전역변수 설정

int playTTS( string sentence ){
    // 출력없는상황에서도 동작하도록 설정
    if(sentence =="NO"){
    }
    else
    {
        // 스피커가 다른 재생을 하지 않고 있을때에만
        if(!s_busy)
        {
            s_busy = true;//바쁘다고 표시
            // tts.php파일을 실행시켜 tts.mp3 파일을 만드는 코드, 혹시 생성되는 파일이름 바꾸려면 tts.php 30번째 줄가서 이름 바꾸면됨
            string cmd = "php tts.php"+sentence;
            system(cmd.c_str());
            //텍스트 재생
            system("omxplayer tts.mp3");
            s_busy = false;//일끝났다고 표시
        }
    }
    return 0;
}

int main(){
    playTTS("hihi");

}
