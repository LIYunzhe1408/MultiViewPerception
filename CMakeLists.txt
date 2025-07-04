cmake_minimum_required(VERSION 3.10)
project(OpenCVTest)

set(CMAKE_CXX_STANDARD 17)

# Find OpenCV
find_package(OpenCV REQUIRED)
if(NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV not found. Please set OpenCV_DIR.")
endif()

# Find RealSense SDK
find_package(realsense2 REQUIRED)
if(NOT realsense2_FOUND)
    message(FATAL_ERROR "RealSense SDK not found. Please ensure librealsense is installed and discoverable by CMake.")
endif()


# Header file search path
include_directories(include)
include_directories(${CMAKE_SOURCE_DIR}/third_party/onnxruntime/include)
link_directories(${CMAKE_SOURCE_DIR}/third_party/onnxruntime/lib)


# Files to be compiled and linked
file(GLOB SOURCES "src/*.cpp")
add_executable(OpenCVTest ${SOURCES} main.cpp)
target_link_libraries(OpenCVTest PRIVATE
    ${OpenCV_LIBS}
    realsense2
    onnxruntime
)