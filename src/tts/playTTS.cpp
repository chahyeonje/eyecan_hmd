#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
bool s_busy=false;

int playTTS( string sentence ){
    
    if(sentence =="NO"){
    }
    else
    {
        
        if(!s_busy)
        {
            s_busy = true;
           
            string cmd = "php tts.php"+sentence;
            system(cmd.c_str());
            
            system("omxplayer tts.mp3");
            s_busy = false;
        }
    }
    return 0;
}

int main(){
    playTTS("hi");

}
