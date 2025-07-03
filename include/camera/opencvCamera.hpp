#ifndef OPENCVCAMERA_HPP
#define OPENCVCAMERA_HPP

#include <opencv2/opencv.hpp>
#include "cameraInterface.hpp"

namespace perception {
namespace camera {

class OpenCVCamera: public CameraInterface{
    public:
        explicit OpenCVCamera(int device_id = 0);
        ~OpenCVCamera() override;

        bool init() override;
        bool getFrame(cv::Mat& frame) override;
    private:
        int device_id_;
        cv::VideoCapture cap_;
};


} // namespace camera    
} // namespace perception


#endif