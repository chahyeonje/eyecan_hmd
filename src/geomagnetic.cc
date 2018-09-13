#include "include/myahrs_plus.hpp"

using namespace WithRobot;
static const int BAUDRATE = 115200;
static const char* DIVIDER = "1";

double geo_yaw;

MyAhrsPlus sensor;
SensorData sensor_data;

void initGeo(){

	std::vector<std::string> serial_device_list;
	serial_device_list.push_back(std::string("/dev/ttyACM0"));

	sensor.start(serial_device_list[0].c_str(), BAUDRATE);
}

void updateGeo(){

	if(sensor.wait_data() == true) {
		sensor.get_data(sensor_data);
		EulerAngle& e = sensor_data.euler_angle;
		printf("yaw : %.2f \n", e.yaw);

		geo_yaw = e.yaw;

		if(geo_yaw < 0)
		{
			geo_yaw += 360;
		}

		printf("yaw : %.2f \n", geo_yaw);

	}
}

