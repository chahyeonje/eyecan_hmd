
#ifndef __curl_h_
#define __curl_h_

using namespace std;

#include <jsoncpp/json/json.h>



int battery;
string rBuffer;	//알릴 메세지
int pin;
int device_id;

string EC; //서버에 보낼 정보
string URL;
string tmp;


size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
string NTOS(double value);
string JTOS(Json::Value Eye);
void initCurl();
bool isBufferEmpty();
void flushBuffer();
void sendData();

#endif




