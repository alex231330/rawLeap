#include <iostream>
#include "include/Leap.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "LeapEventListener.cpp"
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ximgproc.hpp>

using namespace Leap;
using namespace cv;
using namespace cv::ximgproc;

bool isDisconnected = false;
Ptr<StereoBM> left_matcher = StereoBM::create(160, 15);
Ptr<StereoMatcher> right_matcher = createRightMatcher(left_matcher);
Ptr<DisparityWLSFilter> wls_filter = createDisparityWLSFilter(left_matcher);

int lambda = 1, sigma = 1;

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

    //InteractionBox iBox = controller.frame().interactionBox();
    //Leap::Vector leapPoint = pointable.stabilizedTipPosition();
    //Leap::Vector normalizedPoint = iBox.normalizePoint(leapPoint, false);
    
    //int appX = normalizedPoint.x * appWidth;
    //int appY = (1 - normalizedPoint.y) * appHeight; 
    //std::cout << appX - 400 << " " << appY - 810 << "\n";
    Frame frame = controller.frame();
    ImageList images = frame.images();
    Mat leftMat, rightMat;
    Mat leftDisp, rightDisp;
    Mat filteredDisp, filtered_disp_vis;
    if (images.count() >= 2)
    {
        wls_filter->setLambda(float(lambda) / 10);
        wls_filter->setSigmaColor(float(sigma) / 10);

        leftMat = Mat(images[0].height(), images[0].width(), CV_8UC1, (void *)images[0].data());
        rightMat = Mat(images[1].height(), images[1].width(), CV_8UC1, (void *)images[1].data());
        std::cout << "Left Size " << leftMat.cols << " " << leftMat.rows << " Right Size " << rightMat.cols << " " << rightMat.rows << "\n";


        left_matcher->compute(leftMat, rightMat, leftDisp);
        right_matcher->compute(rightMat, leftMat, rightDisp);

        std::cout << leftDisp.depth() << "\n";
        std::cout << leftDisp.empty() << "\n";
        std::cout << leftDisp.channels() << "\n";

        wls_filter->filter(leftDisp, left, filteredDisp, rightDisp);
        getDisparityVis(filtered_disp, filtered_disp_vis);

        //normalize(disp, disp, 0, 255, CV_MINMAX, CV_8UC3);
        imshow("leftMat", leftMat);
        imshow("rightMat", rightMat);
        imshow("Stereo", filtered_disp_vis);
        waitKey(1);
    }
}

int main() {
    /* code */
    bool isConnected = true;
    Leap::Controller controller;
    LeapEventListener listener;

    namedWindow("trackbars", WINDOW_AUTOSIZE);
    createTrackbar("lambda", "trackbars", &lambda, 100);
    createTrackbar("sigma", "trackbars", &sigma, 100);

    std::cout << "Started \n";
    controller.addListener(listener);
    controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);
    controller.setPolicy(Leap::Controller::POLICY_IMAGES);
    std::cin.get();
    return 0;
}