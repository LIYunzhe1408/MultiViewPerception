#include <opencv2/opencv.hpp>
#include <iostream>
#include <librealsense2/rs.hpp>
#include "include/camera/opencvCamera.hpp"
#include "include/camera/realsenseCamera.hpp"    
#include <onnxruntime_cxx_api.h>
#include "include/detector/YOLODetector.hpp"
#include "include/utils/visualizer.hpp"
#include "utils/YAMLLoader.hpp"


int main() {
    using namespace perception;

    std::vector<std::string> class_names = 
        utils::load_class_names_from_yaml("../model/coco_names.yaml");



    camera::OpenCVCamera webcam;
    camera::RealsenseCamera realsense;
    if (!webcam.init() || !realsense.init()) {
        std::cerr << "Camera Initialization failed.\n";
        return -1;
    }
    detector::YOLODetector yolo("../model/yolov5s.onnx");
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
        auto detection1 = yolo.detect(frame_webcam);
        utils::drawDetections(frame_webcam, detection1, class_names);
        
        // Detection
        auto detection2 = yolo.detect(frame_realsense);
        utils::drawDetections(frame_realsense, detection2, class_names);


        // NMS


        // Draw and Show
        cv::imshow("Webcam", frame_webcam);
        cv::imshow("Realsense", frame_realsense);
        if (cv::waitKey(1) == 'q') break;
    }

    // Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "default");
    // Ort::SessionOptions session_options;
    // session_options.SetIntraOpNumThreads(1);

    // Ort::Session session(env, "../model/yolov5s.onnx", session_options);
    // std::cout << "Model loaded successfully!\n";
    return 0;
}
