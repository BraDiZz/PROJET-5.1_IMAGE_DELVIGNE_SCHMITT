# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(color)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

execute_process(COMMAND pkg-config --cflags gtkmm-3.0 OUTPUT_VARIABLE GTKMM_CFLAGS)
execute_process(COMMAND pkg-config --libs gtkmm-3.0 OUTPUT_VARIABLE GTKMM_LIBS)

string(STRIP ${GTKMM_CFLAGS} GTKMM_CFLAGS)
string(STRIP ${GTKMM_LIBS} GTKMM_LIBS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GTKMM_CFLAGS}")

file(GLOB SOURCE_FILES "src/*.cpp")

add_executable(Color ${SOURCE_FILES})

target_link_libraries(Color ${GTKMM_LIBS})