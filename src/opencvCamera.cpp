#include "camera/opencvCamera.hpp"

namespace perception {
namespace camera {

OpenCVCamera::OpenCVCamera(int device_id): device_id_(device_id) {}

OpenCVCamera::~OpenCVCamera() {
    if (cap_.isOpened()) {
        cap_.release();
    }
}

bool OpenCVCamera::init() {
    cap_.open(device_id_);
    if (!cap_.isOpened()) {
        std::cerr << "Error: Could not open camera!" << std::endl;
        return false;
    }
    cap_.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap_.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    return true;
}

bool OpenCVCamera::getFrame(cv::Mat& frame) {
    if (!cap_.isOpened()) return false;
    cap_ >> frame;
    return !frame.empty();
}
}
}