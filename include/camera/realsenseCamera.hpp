#ifndef REALSENSECAMERA_HPP
#define REALSENSECAMERA_HPP


#include <librealsense2/rs.hpp>
#include "camera/cameraInterface.hpp"

namespace perception {
namespace camera {

class RealsenseCamera: public CameraInterface {
    public:
        explicit RealsenseCamera();
        ~RealsenseCamera() override;

        bool init() override;
        bool getFrame(cv::Mat& frame) override;
    private:
        rs2::pipeline pipe_;
        rs2::config cfg_;
};

}
}

#endif