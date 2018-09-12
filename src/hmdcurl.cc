
#include <iostream>
#include <curl/curl.h>
#include <string>
#include <jsoncpp/json/json.h>
#include <stdlib.h>
#include <unistd.h>
#include <sstream>

#include "include/hmdgps.h"
#include "include/switch.h"
/*
using namespace std;

//밖에서 불러올 변수 
extern double geo_yaw;
extern double gps_lat;
extern double gps_long;
extern int sw1;
extern int sw2;
extern int sw3;
extern int sw4;
extern int sw5;
//여기서만 쓸 변수 
int pin;
int device_id=12345;
int battery=76;
string rBuffer;	//알릴 메세지
string EC; //서버에 보낼 정보
string URL="https://eyecan.tk/rest_api/map_api?";
string tmp; //서버에서 받는 정보
*/


//int geo_yaw_=(int)geo_yew;

//버퍼 비우기
void flushBuffer()
{
	//tmp="";
    	//cout<<"flushBuffer()"<<endl;
}
/*
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((string*)userp)->append((char*)contents, size*nmemb);
	return size * nmemb;
}

//number to string
string NTOS(double value){
    	ostringstream strs;
    	strs << value;
    	return strs.str();
}

//json to string
string JTOS(Json::Value Eye){
    	ostringstream strs;
    	strs << Eye;
    	return strs.str();
}
*/

//통신초기화
void initCurl()
{
    /*
    	flushBuffer();
    	if(sw1==1)
        	pin=1;
    	else if(sw2==1)
        	pin=2;
    	else if(sw3==1)
        	pin=3;
    	else if(sw4==1)
       		pin=4;
    	else if(sw5==1)
        	pin=8;
    	else
        	pin=9;

    	if(pin == 4){ //sos
        	EC="https://eyecan.tk/rest_api/sos_api?device_id="+NTOS(device_id);
	}
    	else {
        	EC=URL+"device_id="+NTOS(device_id)
           		+"&index="+NTOS(pin)
            		+"&battery="+NTOS(battery)
            		+"&locationX="+NTOS(gps_long)
            		+"&locationY="+NTOS(gps_lat)
            		+"&angle="+NTOS(geo_yaw_);
    	}
  	//cout<<"initCurl()"<<endl;
    */
}

//버퍼가 비었는지 확인
bool isBufferEmpty()
{
    /*
  	if(tmp=="")
    		return true;
  	else
    		return false;
   	// cout<<"isBufferEmpty()"<<endl;
*/
}


//버퍼에 데이터 보내기
void sendData()
{
    /*
  	initCurl();
  	CURL *curl;
	CURLcode res;
  	struct curl_slist *headerlist=NULL;

	if(curl){

    		headerlist=curl_slist_append(headerlist, "Content-Type:application/json");
  		headerlist=curl_slist_append(headerlist, "Accept: application/json");
  		headerlist=curl_slist_append(headerlist, "charsets: utf-8");
    		curl = curl_easy_init();
    		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
    		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    		cuurl_easy_setopt(curl, CURLOPT_URL, EC.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &tmp);

		res = curl_easy_perform(curl);
    		if(res != CURLE_OK){
        		return;
    		}	
		curl_easy_cleanup(curl);
    		Json::Value Eyecan;
    		Json::Reader reader;
    		reader.parse( tmp, Eyecan );

    		rBuffer=JTOS(Eyecan["message"]);
    		if(pin==8||pin==9){
      			rBuffer="";
     		}
    		else if(pin==1||pin==2||pin==3||pin==4){
      			rBuffer=JTOS(Eyecan["message"]);
     		}
    	//code_num=JTOS(Eyecan["code_num"]);
	//cout<<"sendData()"<<endl;
	}
*/
}
