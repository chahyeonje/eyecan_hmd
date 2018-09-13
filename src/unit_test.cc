
#include <cstdio>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include <utility>
#include <vector>
#include <iostream>

#include "include/hmdgps.h"
#include "include/geomagnetic.h"
#include "include/switch.h"
#include "include/hmdcurl.h"
#include "include/speaker.h"
#include "include/camera.h"




int main()
{
    cout<<"test started!"<<endl;

    updateGPS();
    initGPS();
    return 0;
}
