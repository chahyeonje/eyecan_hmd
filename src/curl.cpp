
#include <iostream>
#include <curl/curl.h>
#include <string>
#include <jsoncpp/json/json.h>
#include <stdlib.h>
#include <unistd.h>
#include <sstream>
#include <cstdlib>
#include <cstring>

#include "hmdgps.h"
//#include "include/switch.h"
//#include "include/geomagnetic.h"
using namespace std;

double geo_yaw=123.2;
//double gps_long=129.074141;
//double gps_lat=35.2331576;
int sw1=1;  //23
int sw2=0; //24
int sw3=0; //27
int sw4=0; //22
int sw5=0; //17

int pin;
int device_id=5678;
int battery=76;
string rBuffer; 
string EC; 
string URL="http://eyecan.ml/rest_api/map_api?";
string tmp; 



int geo_yaw_=(int)geo_yaw;
int _gps_lat;
int _gps_long;




void flushBuffer()
{
	tmp="";
    	//cout<<"flushBuffer()"<<endl;
}
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



void initCurl()
{


    	flushBuffer();

/*
 *
 *
 */
	updateGPS();

	/*
	 *
	 *
	 */

	_gps_lat =(int)gps_lat;
	_gps_long =(int)gps_long;


    	if(sw1==1)
        	pin=1;
    	else if(sw2==1)
        	pin=2;
    	else if(sw3==1)
        	pin=3;
    	else if(sw4==1)//sos
       		pin=4;
    	else if(sw5==1)//jumja
        	pin=8;
    	else
        	pin=9;//deagi

    	if(pin == 4){ //sos
        	EC="http://eyecan.ml/rest_api/sos_api?device_id="+NTOS(device_id);
	}
    	else {
        	EC=URL+"device_id="+NTOS(device_id)
           		+"&index="+NTOS(pin)
            		+"&battery="+NTOS(battery)
            		+"&locationX="+NTOS(_gps_long)
            		+"&locationY="+NTOS(_gps_lat)
            		+"&angle="+NTOS(geo_yaw_);
    	}
  	//cout<<"initCurl()"<<endl;
    
}


bool isBufferEmpty()
{

  	if(tmp=="")
    		return true;
  	else
    		return false;
   	// cout<<"isBufferEmpty()"<<endl;

}



void sendData()
{

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
    		curl_easy_setopt(curl, CURLOPT_URL, EC.c_str());
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
	cout<<rBuffer<<endl;
	}

}




//테스트용 

int main()
{

/*
 */

	initGPS();


	/*
	 */


	while(1){

		//playTTS(rBuffer);
		//for(int i=0; i<2 ;i++){

			sendData();
			sleep(0.5);
			cout<<gps_long<<"  "<<gps_lat<<endl;
			printf("%d \n",_gps_lat);	
	//	}

	}

  

	return 0;

}
