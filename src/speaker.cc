#include<iostream>
#include <cstring>

using namespace std;

int bpm=0;//bit per minute
bool s_busy = false;

void initSpeaker()
{
    cout<<"initSpeaker()\n";
}
void playBeep()
{
    //비프음을 재생함
    cout<<"Beep!\n";
}

void changeBeep(int b)
{
    cout<<"changeBeep()\n";
    bpm =b;
}
/*
void playTTS( string rBuffer ){
    
    if(rBuffer =="NO"){
    }
    else
    {
        
        if(!s_busy)
        {
            s_busy = true;
            
            string cmd = "php tts.php "+rBuffer;
            system(cmd.c_str());
            
            system("omxplayer tts.mp3");
            s_busy = false;
            
        }
    }
    
}
*/
void playTTS(char* str)
{
    //스피커가 다른 재생을 하지 않고 있을때에만
    if(!s_busy)
    {
        s_busy = true;//바쁘다고 표시
        //텍스트 재생
        cout<<"playTTS\n";
        s_busy = false;//일끝났다고 표시
    }

    //해당 스트링 재생
}



