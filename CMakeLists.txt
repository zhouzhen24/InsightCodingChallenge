cmake_minimum_required(VERSION 2.8)

project("Insight Coding Chanllenge")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories(${CMAKE_SOURCE_DIR}/external)
add_executable(../insight src/main.cpp src/Hashtag.cpp)

