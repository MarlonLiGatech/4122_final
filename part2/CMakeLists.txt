cmake_minimum_required(VERSION 3.9)
project(p32)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")

find_package(MPI REQUIRED)

include_directories(SYSTEM ${MPI_INCLUDE_PATH})

set(SOURCE_FILES
    complex.cc
    complex.h
    input_image.cc
    input_image.h
    p32.cc
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${MPI_LIBRARIES})