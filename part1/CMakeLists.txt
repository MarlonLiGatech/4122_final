cmake_minimum_required(VERSION 3.8)
project(p31)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")

set(SOURCE_FILES
    complex.cc
    complex.h
    input_image.cc
    input_image.h
    p31.cc
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})