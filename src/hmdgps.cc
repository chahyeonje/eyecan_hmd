extern "C"
{
#include "include/gps.h"
}
#include <iostream>
using namespace std;
double gps_lat;
double gps_long;

void initGPS(){
    cout<<"initGPS()"<<endl;
	gps_init();
    
}

void updateGPS(){
    cout<<"updateGPS()"<<endl;
	loc_t data;
	gps_location(&data);

	gps_lat = data.latitude;
	gps_long = data.longitude;
}
