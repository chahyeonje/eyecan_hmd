extern "C"
{
#include "include/gps.h"
}
#include <cstdio>
double gps_lat;
double gps_long;

void initGPS(){
	gps_init();
}

void updateGPS(){
    cout<<"void updateGPS()"<<endl;
	loc_t data;
	gps_location(&data);

	gps_lat = data.latitude;
	gps_long = data.longitude;
}
