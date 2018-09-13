extern "C"
{
#include "include/gps.h"
}
double gps_lat;
double gps_long;

void initGPS(){
	gps_init();
}

void updateGPS(){

	loc_t data;
	gps_location(&data);

	gps_lat = data.latitude;
	gps_long = data.longitude;
}
