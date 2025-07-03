#ifndef CAMERAINTERFACE_HPP
#define CAMERAINTERFACE_HPP

#include <opencv2/core.hpp>

namespace perception{
namespace camera{

class CameraInterface{
    public:
        virtual ~CameraInterface() = default;
        virtual bool init() = 0;
        virtual bool getFrame(cv::Mat& frame) = 0;
};

}
} // namespace perception

#endif