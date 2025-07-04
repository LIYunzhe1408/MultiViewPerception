cmake_minimum_required(VERSION 3.10)
project(OpenCVTest)

set(CMAKE_CXX_STANDARD 17)

# Find OpenCV
find_package(OpenCV REQUIRED)
if(NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV not found.")
endif()

# Find RealSense SDK
find_package(realsense2 REQUIRED)
if(NOT realsense2_FOUND)
    message(FATAL_ERROR "RealSense SDK not found.")
endif()

find_package(yaml-cpp REQUIRED)


# Source files
file(GLOB SOURCES "src/*.cpp")  
add_executable(OpenCVTest ${SOURCES} main.cpp)  

# Include directories
target_include_directories(OpenCVTest PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/third_party/onnxruntime/include
)

# Link ONNX and others
target_link_directories(OpenCVTest PRIVATE ${PROJECT_SOURCE_DIR}/third_party/onnxruntime/lib)
target_link_libraries(OpenCVTest PRIVATE
    ${OpenCV_LIBS}
    realsense2
    onnxruntime
    yaml-cpp
)
