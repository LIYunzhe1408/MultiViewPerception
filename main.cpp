#include <opencv2/opencv.hpp>
#include <iostream>
#include <librealsense2/rs.hpp>
#include "include/camera/opencvCamera.hpp"
#include "include/camera/realsenseCamera.hpp"

void webcam() {
    // Open the default camera (0 = first camera)
    cv::VideoCapture cap(0); 

    // Check if the camera opened successfully
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera!" << std::endl;
    }

    // Create a window to display the video feed
    cv::namedWindow("Camera Feed", cv::WINDOW_NORMAL);

    // Continuously capture frames until the user presses 'q'
    while (true) {
        cv::Mat frame;
        
        // Capture a new frame from the camera
        cap >> frame; 

        // Check if the frame was successfully captured
        if (frame.empty()) {
            std::cerr << "Error: Blank frame grabbed!" << std::endl;
            break;
        }

        // Display the captured frame in the window
        cv::imshow("Camera Feed", frame);

        // Wait for 1 ms and check if 'q' is pressed to quit
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    // Release the camera and close the window
    cap.release();
    cv::destroyAllWindows();
}


void realsense() {
    rs2::pipeline pipe;
    rs2::config cfg;
    cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);
    cfg.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 30);

    
    pipe.start(cfg);  // Start with default configuration


    while (true) {
        rs2::frameset frames = pipe.wait_for_frames();
        rs2::video_frame color_frame = frames.get_color_frame();

        int w = color_frame.get_width();
        int h = color_frame.get_height();

        cv::Mat color(cv::Size(w, h), CV_8UC3, (void*)color_frame.get_data(), cv::Mat::AUTO_STEP);

        cv::imshow("color frame", color);
        if (cv::waitKey(1) == 'q') break;
    }
}


int main() {
    // webcam();
    // realsense();
    using namespace perception;

    // camera::OpenCVCamera webcam;
    camera::RealsenseCamera realsense;
    // if (!webcam.init()) {
    //     std::cerr << "Webcam - Initialization failed.\n";
    //     return -1;
    if (!realsense.init()) {
        std::cerr << "Realsense - Initialization failed.\n";
        return -1;
    }

    // cv::Mat frame;
    cv::Mat frame_realsense;

    while(true) {
        // if (!webcam.getFrame(frame)){
        //     std::cerr << "Image read failed.\n";
        //     continue;
        // }
        if (!realsense.getFrame(frame_realsense)) {
            std::cerr << "Realsense - Image read failed.\n";
            continue;
        }
        cv::imshow("Realsense", frame_realsense);
        if (cv::waitKey(1) == 'q') break;
    }
    return 0;
}
