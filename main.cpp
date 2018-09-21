#include <iostream>
#include "include/Leap.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "LeapEventListener.cpp"

using namespace Leap;
using namespace cv;

int main(int argc, char const *argv[])
{
    /* code */
    Leap::Controller controller;
    LeapEventListener listener;
    controller.addListener(listener);
    controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);
    if (controller.isConnected()){
        std::cout << "Leap motion connected! \n";
    }else{
        std::cout << "Leap motion disconneted! \n";
    }
    return 0;
}
