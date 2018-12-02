#include <sstream>
#include <string>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"
#include "opencv2/xfeatures2d.hpp"
#include <stdlib.h>
#include <vector>
#include <cstdlib>
#include <unistd.h>

using namespace cv;
using namespace std;

// image matrix for input

VideoCapture cap;
Mat dst;
Mat frame;
//vector<Point3f> pixelData;

void initCamera()   // State: Turn on -> loop /Turn out-> sleep
{  //Starting with initialize
    // 1. Get cam impormation
    cout<<"initCamera()"<<endl;
    cap.open(0);// OR advance usage: select any API backend
    int deviceID = 0;             // 0 = open default camera
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    // open selected camera using selected API
    cap.open(deviceID + apiID);
    //Type : jpg
    
    if (!cap.isOpened())
    {
        cerr << "ERROR! Unable to open camera\n";
    }
    cout<<"camera opend!"<<endl;
}

void updatePixel()
{ //Update global variable when call
    cout<<"updatePixel()"<<endl;
    if (cap.isOpened()) {
        
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);
        cout<<"updatePixel2()"<<endl;
        // check if we succeeded
        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
        }
    
        resize(frame, dst, Size(384, 384), cv::INTER_LINEAR);
        // We will use dst
        // show live and wait for a key with timeout long enough to show images
        //imshow("Image", dst);
        //dst.convertTo(dst, CV_32FC3);
        //sleep(1);
    }
    else
    {
        cout << "camera open 안됨!\n";
    }
    cout<<"updatePixel()2"<<endl;
}
