// src/Visualizer.cpp
#include "utils/visualizer.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <string>

namespace perception::utils {

void drawDetections(cv::Mat& image,
                    const std::vector<perception::detector::Detection>& detections,
                    const std::vector<std::string>& class_names) {
    for (const auto& det : detections) {
        // 颜色
        cv::Scalar color(50 + (det.class_id * 30) % 200, 255 - (det.class_id * 20) % 200, (det.class_id * 80) % 255);

        // 类别名
        std::string name = (det.class_id >= 0 && det.class_id < class_names.size())
                           ? class_names[det.class_id] : "unknown";
        std::string label = name + " " + cv::format("%.2f", det.confidence);

        // 画框 + 标签
        cv::rectangle(image, det.box, color, 2);
        int baseline = 0;
        cv::Size textSize = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseline);
        cv::Rect textBg(det.box.tl().x, det.box.tl().y - textSize.height - 2, textSize.width + 4, textSize.height + 4);
        textBg &= cv::Rect(0, 0, image.cols, image.rows);

        cv::rectangle(image, textBg, color, cv::FILLED);
        cv::putText(image, label, det.box.tl() + cv::Point(2, -2), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,0,0), 1);
    }
}

}
