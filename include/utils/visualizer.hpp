// include/utils/Visualizer.hpp
#pragma once
#include "detector/detection.hpp"
#include <opencv2/core.hpp>
#include <vector>
#include <string>

namespace perception::utils {

void drawDetections(cv::Mat& image,
                    const std::vector<perception::detector::Detection>& detections,
                    const std::vector<std::string>& class_names);

}
