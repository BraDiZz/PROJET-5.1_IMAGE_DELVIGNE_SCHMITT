# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(color)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

file(GLOB SOURCE_FILES "src/*.cpp")

add_executable(Color ${SOURCE_FILES})