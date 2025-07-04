// src/YOLODetector.cpp
#include "detector/YOLODetector.hpp"
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdexcept>

namespace perception::detector {

YOLODetector::YOLODetector(const std::string& model_path)
    : env(ORT_LOGGING_LEVEL_WARNING, "YOLO"),
      session_options{},
      session(env, model_path.c_str(), session_options),
      allocator{}
{
    std::cout << "[INFO] YOLO model loaded from: " << model_path << std::endl;
}

std::vector<float> YOLODetector::preprocess(const cv::Mat& image) {
    cv::Mat resized;
    cv::resize(image, resized, {640, 640});
    resized.convertTo(resized, CV_32F, 1.0 / 255.0);

    std::vector<float> input_tensor(3 * 640 * 640);
    for (int c = 0; c < 3; ++c)
        for (int y = 0; y < 640; ++y)
            for (int x = 0; x < 640; ++x)
                input_tensor[c * 640 * 640 + y * 640 + x] = resized.at<cv::Vec3f>(y, x)[c];
    return input_tensor;
}

std::vector<Detection> YOLODetector::detect(const cv::Mat& image) {
    if (image.empty()) {
        std::cerr << "[WARN] Empty image passed to detect(). Skipping.\n";
        return {};
    }

    std::vector<float> input_tensor_values = preprocess(image);
    std::array<int64_t, 4> input_shape = {1, 3, 640, 640};

    Ort::MemoryInfo memory_info = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
    Ort::Value input_tensor = Ort::Value::CreateTensor<float>(
        memory_info, input_tensor_values.data(), input_tensor_values.size(),
        input_shape.data(), input_shape.size());

    auto input_name_ptr = session.GetInputNameAllocated(0, allocator);
    auto output_name_ptr = session.GetOutputNameAllocated(0, allocator);
    const char* input_name = input_name_ptr.get();
    const char* output_name = output_name_ptr.get();

    auto output_tensors = session.Run(
        Ort::RunOptions{nullptr},
        &input_name, &input_tensor, 1,
        &output_name, 1
    );

    float* output = output_tensors[0].GetTensorMutableData<float>();
    auto shape = output_tensors[0].GetTensorTypeAndShapeInfo().GetShape();  // [1, N, 85]
    int64_t num_boxes = shape[1];
    int64_t num_attrs = shape[2];

    std::vector<Detection> results;
    for (int i = 0; i < num_boxes; ++i) {
        float* row = output + i * num_attrs;
        float conf = row[4];
        if (conf < 0.25f) continue;

        float max_prob = 0.0f;
        int class_id = -1;
        for (int j = 5; j < num_attrs; ++j) {
            if (row[j] > max_prob) {
                max_prob = row[j];
                class_id = j - 5;
            }
        }

        if (max_prob * conf < 0.25f) continue;

        float cx = row[0], cy = row[1], w = row[2], h = row[3];
        int x = static_cast<int>((cx - w / 2) * image.cols / 640);
        int y = static_cast<int>((cy - h / 2) * image.rows / 640);
        int ww = static_cast<int>(w * image.cols / 640);
        int hh = static_cast<int>(h * image.rows / 640);

        results.push_back(Detection{cv::Rect(x, y, ww, hh), max_prob * conf, class_id});
    }

    return results;
}

}
