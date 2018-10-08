#include <iostream>
#include "include/Leap.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "LeapEventListener.cpp"
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace Leap;
using namespace cv;

bool isDisconnected = false;
const unsigned int cmWidth = 256;
const unsigned int cmHeight = 256;
float calibMap[cmWidth*cmHeight * 2];


Mat disp;

void LeapEventListener::onConnect(const Controller& controller) {
    std::cout << "Connected" << std::endl;
    isDisconnected = 0;
    // Enable gestures, set Config values:
}

//Not dispatched when running in a debugger
void LeapEventListener::onDisconnect(const Controller& controller) {
    isDisconnected = 1;
    std::cout << "Disconnected" << std::endl;
}

void LeapEventListener::onFrame(const Controller& controller) {
    std::cout << "New frame available" << std::endl;
    int appWidth = 800;
    int appHeight = 600;

    Pointable pointable = controller.frame().pointables().frontmost();
    std::cout << controller.frame().tools().count() << "\n";
    Frame frame = controller.frame();
    ImageList images = frame.images();
    Mat leftMat, rightMat;
    Mat leftDisp, rightDisp;
    if (images.count() >= 2)
    {
     
        leftMat = Mat(images[0].height(), images[0].width(), CV_8UC1, (void *)images[0].data());
        rightMat = Mat(images[1].height(), images[1].width(), CV_8UC1, (void *)images[1].data());

        //normalize(disp, disp, 0, 255, CV_MINMAX, CV_8UC3);
        imshow("leftMat", leftMat);
        imshow("rightMat", rightMat);
        imshow("Stereo", disp);
        waitKey(1);
    }
}

int main() {
    /* code */
    bool isConnected = true;
    Leap::Controller controller;
    LeapEventListener listener;
	for (unsigned int y = 0; y < cmHeight; ++y)
		for (unsigned int x = 0; x < cmWidth; ++x)
		{
			float xx = (float)x / (float)cmWidth;
			xx = xx*2.0f; 
			float yy = (float)y / (float)cmHeight;

			calibMap[y*cmWidth * 2 + 2 * x] = xx;
			calibMap[y*cmWidth * 2 + 2 * x + 1] = yy;
		}

    std::cout << "Started \n";
    controller.addListener(listener);
    controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);
    controller.setPolicy(Leap::Controller::POLICY_IMAGES);
    std::cin.get();
    return 0;
}