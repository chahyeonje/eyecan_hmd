#include <iostream>
using namespace std;
/*
#include <wiringPi.h>
*/
const int swPin_1 = 17;//pin 11(GPIO 17)
const int swPin_2 = 18;//pin 12(GPIO 18) 
const int swPin_3 = 27;//pin 13(GPIO 27)
const int swPin_4 = 22;//pin 15(GPIO 22)
const int swPin_5 = 23;//pin 16(GPIO 23)

int sw1;
int sw2;
int sw3;
int sw4;
int sw5;

void initSwitch()
{
    cout<<"initSwitch()"<<endl;
    /*
    wiringPiSetupGpio();

    pinMode(swPin_1, INPUT);//버튼을 위해 입력으로 설정
    pinMode(swPin_2, INPUT);//버튼을 위해 입력으로 설정
    pinMode(swPin_3, INPUT);//버튼을 위해 입력으로 설정
    pinMode(swPin_4, INPUT);//버튼을 위해 입력으로 설정
    pinMode(swPin_5, INPUT);//버튼을 위해 입력으로 설정

    pullUpDnControl(swPin_1, PUD_UP); 
    pullUpDnControl(swPin_2, PUD_UP);
    pullUpDnControl(swPin_3, PUD_UP);
    pullUpDnControl(swPin_4, PUD_UP);
    pullUpDnControl(swPin_5, PUD_UP);

    sw1 = digitalRead(swPin_1);	
    sw2 = digitalRead(swPin_2);
    sw3 = digitalRead(swPin_3);
    sw4 = digitalRead(swPin_4);
    sw5 = digitalRead(swPin_5);
     */
}

void updateSwitch()
{
    /*
    sw1 = digitalRead(swPin_1);	
    sw2 = digitalRead(swPin_2);
    sw3 = digitalRead(swPin_3);
    sw4 = digitalRead(swPin_4);
    sw5 = digitalRead(swPin_5);
     */
}
