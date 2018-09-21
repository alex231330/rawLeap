#include <iostream>
#include "include/Leap.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "LeapEventListener.cpp"

using namespace Leap;
using namespace cv;


bool isDisconnected = false;

void LeapEventListener::onConnect(const Controller& controller) {
    std::cout << "Connected" << std::endl;
    isDisconnected = 0;
    // Enable gestures, set Config values:
    controller.config().setFloat("Gesture.Swipe.MinLength", 200.0);
    controller.config().save();
}

//Not dispatched when running in a debugger
void LeapEventListener::onDisconnect(const Controller& controller) {
    isDisconnected = 1;
    std::cout << "Disconnected" << std::endl;
}

void LeapEventListener::onFrame(const Controller& controller) {
    std::cout << "New frame available" << std::endl;
    Frame frame = controller.frame();
    // Process this frame's data...
}

int main() {
    /* code */
    bool isConnected = true;
    Leap::Controller controller;
    LeapEventListener listener;
    controller.addListener(listener);
    while(1) {
        std::cout << isDisconnected << "\n";
        if (waitKey(100) == 27) { //esc button
            std::cout << "esc key is pressed \n";
            break;
        }
    }
    return 0;
}
