#include "camera/realsenseCamera.hpp"

namespace perception {
namespace camera {

RealsenseCamera::RealsenseCamera() {}

RealsenseCamera::~RealsenseCamera() {

}

bool RealsenseCamera::init() {
    cfg_.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);
    cfg_.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 30);
    pipe_.start(cfg_);  // Start with default configuration
    return true;
}

bool RealsenseCamera::getFrame(cv::Mat& frame) {
    rs2::frameset frames = pipe_.wait_for_frames();
    rs2::video_frame color_frame = frames.get_color_frame();

    int w = color_frame.get_width();
    int h = color_frame.get_height();

    cv::Mat color(cv::Size(w, h), CV_8UC3, (void*)color_frame.get_data(), cv::Mat::AUTO_STEP);
    frame = color;
    return !frame.empty();
}


}
}