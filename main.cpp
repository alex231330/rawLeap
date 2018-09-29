#include <iostream>
#include "include/Leap.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "LeapEventListener.cpp"

using namespace Leap;
using namespace cv;


bool isDisconnected = false;
Mat src;

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
    Frame frame = controller.frame();
    ImageList images = frame.images();
    Mat leftMat;
    Mat rightMat;
    if (images.count() >= 2)
    {
        leftMat = Mat(images[0].height(), images[0].width(), CV_8UC1, (void *)images[0].data());
        rightMat = Mat(images[1].height(), images[1].width(), CV_8UC1, (void *)images[1].data());
        imshow("leftMat", leftMat);
        imshow("rightMat", rightMat);
        waitKey(1);
    }
}

int main() {
    /* code */
    bool isConnected = true;
    Leap::Controller controller;
    LeapEventListener listener;
    std::cout << "Started \n";
    controller.addListener(listener);
    controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);
    controller.setPolicy(Leap::Controller::POLICY_IMAGES);
    std::cin.get();
    return 0;
}