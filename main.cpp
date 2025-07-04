#include <opencv2/opencv.hpp>
#include <iostream>
#include <librealsense2/rs.hpp>
#include "include/camera/opencvCamera.hpp"
#include "include/camera/realsenseCamera.hpp"

int main() {
    using namespace perception;

    camera::OpenCVCamera webcam;
    camera::RealsenseCamera realsense;
    if (!webcam.init() || !realsense.init()) {
        std::cerr << "Camera Initialization failed.\n";
        return -1;
    }

    cv::Mat frame_webcam;
    cv::Mat frame_realsense;

    while(true) {
        if (!webcam.getFrame(frame_webcam)){
            std::cerr << "Webcam - Image read failed.\n";
            continue;
        }
        if (!realsense.getFrame(frame_realsense)) {
            std::cerr << "Realsense - Image read failed.\n";
            continue;
        }
        cv::imshow("Webcam", frame_webcam);
        cv::imshow("Realsense", frame_realsense);
        if (cv::waitKey(1) == 'q') break;
    }
    return 0;
}
