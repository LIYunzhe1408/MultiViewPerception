# MultiViewPerception
This repo is created for engineering skills practice in the autonoumous vehicle field, especially for c++ application. We implemented a tiny close-loop perception pipeline with C++ features including template, classes, functions, modularity, and etc.

## Update Log
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
