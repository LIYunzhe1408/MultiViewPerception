# MultiViewPerception
This repo is created for engineering skills practice in the autonoumous vehicle field, especially for c++ application. We implemented a tiny close-loop perception pipeline with C++ features including template, classes, functions, modularity, and etc.

## Update Log
July 3, 2025. Update `class RealsenseCamera` and integrate two cameras.
July 2, 2025. Update `class OpenCVCamera`.
July 1, 2025. Environment set up and make the camera working.



## Environment
### Hardware
OS: Ubuntu 20.04.6 LTS on VMWare \
VM Settings: Enable USB 3.0 for external cameras and disconnect it from the host. \
Camera: Legion internal camera, Intel Realsense D435i 
### Library
OpenCV: Simply `sudo apt install libopencv-dev` for basic usage. Install from source code if advanced features are needed. \
Realsense: Checkout this guide https://dev.intelrealsense.com/docs/compiling-librealsense-for-linux-ubuntu-guide 

## Compile and Run
Option 1(For demo test): Simply ``` g++ main.cpp -o main `pkg-config --cflags --libs opencv4` ``` \
Option 2(Recommended for larger project): Use CMakeLists, then `mkdir builld && cd build`. Then `cmake ..` + `make` 

## Development Details
### Yolo to ONNX
**IF YOU WANT REVISE ONNX RUNTIME SOURCE CODE LATER, MAKE SURE YOU INSTALL python>=3.10.**
```
conda create -n yolo-onnx python=3.8 -y
conda activate yolo-onnx
pip install torch torchvision onnx onnxruntime
pip install -r https://raw.githubusercontent.com/ultralytics/yolov5/master/requirements.txt
git clone https://github.com/ultralytics/yolov5
cd yolov5/
python export.py --weights yolov5s.pt --include onnx --opset 12
```
Then you will have a `yolo5s.onnx` at your pulled `yolov5/` folder. Test the onnx runtime by running
`python3 -c "import onnxruntime; print(onnxruntime.get_device())`, the output should be either `cpu` or `gpu`

Regarding the model, you can write up a script to test if the model can be loaded
```
// test_onnx.py
import onnxruntime as ort
ort.InferenceSession("./model/yolov5s.onnx")
print("ONNX model loaded!")
```
### ONNX Runtime in C++ on Ubuntu
A `third_party` folder is recommended to build for onnx runtime. `mkdir third_party`
```
MultiViewPerception/
├── CMakeLists.txt
├── models/
│   └── yolov5s.onnx
├── third_party/
│   └── onnxruntime/
│       ├── include/
│       │   └── onnxruntime_cxx_api.h ...
│       └── lib/
│           └── libonnxruntime.so
```
Download pre-compiled package and move it into `third_party/onnxruntime/` by running 
```
wget https://github.com/microsoft/onnxruntime/releases/download/v1.17.3/onnxruntime-linux-x64-1.17.3.tgz
tar -xzvf onnxruntime-linux-x64-1.17.3.tgz
mv onnxruntime-linux-x64-1.17.3 third_party/onnxruntime
```

If you want to revise onnx source code, make sure your env is `>python 3.10`. Then, `cd third_party` folder, clone this onnx repo.
```
git clone --recursive https://github.com/microsoft/onnxruntime
cd onnxruntime
./build.sh --config Release --build_shared_lib --parallel
```

In addition, update CMakeLists to include onnx.
```
include_directories(${CMAKE_SOURCE_DIR}/third_party/onnxruntime/include)
link_directories(${CMAKE_SOURCE_DIR}/third_party/onnxruntime/lib)
target_link_libraries(your_target_name onnxruntime)
```

To test if it works,
```
#include <onnxruntime_cxx_api.h>
#include <iostream>

int main() {
    Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "default");
    Ort::SessionOptions session_options;
    session_options.SetIntraOpNumThreads(1);

    Ort::Session session(env, "../model/yolov5s.onnx", session_options);
    std::cout << "Model loaded successfully!\n";

    return 0;
}
```