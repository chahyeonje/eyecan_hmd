
#ifndef __curl_h_
#define __curl_h_

using namespace std;
/*
#include <jsoncpp/json/json.h>


extern int geo_yaw;
extern double gps_lat;
extern double gps_long;
int battery;
string rBuffer;	//알릴 메세지
extern int sw1;
extern int sw2;
extern int sw3;
extern int sw4;
extern int sw5;
int pin;
int device_id;

string EC; //서버에 보낼 정보
string URL;
string tmp;

*/
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
//string NTOS(double value);
//string JTOS(Json::Value Eye);
void initCurl();
bool isBufferEmpty();
void flushBuffer();
void sendData();

#endif




