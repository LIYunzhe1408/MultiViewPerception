// detector/Detection.hpp
#pragma once
#include <opencv2/core.hpp>

namespace perception::detector {

struct Detection {
    cv::Rect box;
    float confidence;
    int class_id;
};

}
