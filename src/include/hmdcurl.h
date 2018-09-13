#ifndef __curl_h_
#define __curl_h_



using namespace std;

extern string rBuffer;	//알릴 메세지

//size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
//string NTOS(double value);
//string JTOS(Json::Value Eye);
void initCurl();
bool isBufferEmpty();
void flushBuffer();
void sendData();

#endif




