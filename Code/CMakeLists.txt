# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(color)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

execute_process(COMMAND pkg-config --cflags --libs gtkmm-3.0 OUTPUT_VARIABLE PKG_CONFIG_OUTPUT)
string(STRIP ${PKG_CONFIG_OUTPUT} PKG_CONFIG_OUTPUT)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PKG_CONFIG_OUTPUT}")

file(GLOB SOURCE_FILES "src/*.cpp")

add_executable(Color ${SOURCE_FILES})