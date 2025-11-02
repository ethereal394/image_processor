cmake_minimum_required(VERSION 3.28)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

add_executable(
        image_processor
        image_processor.cpp
        parser.cpp
        exception.cpp
        controller.cpp
        image.cpp
        io.cpp
        filters/base_filters.cpp
        filters/crop.cpp
        filters/grayscale.cpp
        filters/negative.cpp
        filters/sharpening.cpp
        filters/edge_detection.cpp
        filters/compress.cpp
        filters/gaussian_blur.cpp
        factories/base_factory.cpp
        factories/crop_factory.cpp
        factories/grayscale_factory.cpp
        factories/negative_factory.cpp
        factories/sharpening_factory.cpp
        factories/edge_detection_factory.cpp
        factories/compress_factory.cpp
        factories/gaussian_blur_factory.cpp
)
