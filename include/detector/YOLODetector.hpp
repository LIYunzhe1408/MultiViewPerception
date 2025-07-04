// include/detector/YOLODetector.hpp
#pragma once

#include "detection.hpp"
#include <onnxruntime_cxx_api.h>
#include <opencv2/core.hpp>
#include <string>
#include <vector>

namespace perception::detector {

class YOLODetector {
public:
    explicit YOLODetector(const std::string& model_path);

    // 主检测接口，输入 OpenCV 图像，输出检测结果
    std::vector<Detection> detect(const cv::Mat& image);

private:
    // 预处理图像
    std::vector<float> preprocess(const cv::Mat& image);

private:
    Ort::Env env;
    Ort::SessionOptions session_options;
    Ort::Session session;
    Ort::AllocatorWithDefaultOptions allocator;
};

}  // namespace perception::detector
