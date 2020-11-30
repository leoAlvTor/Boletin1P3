cmake_minimum_required(VERSION 3.17)
project(Boletin1P3)

set(CMAKE_CXX_STANDARD 14)

add_executable(Boletin1P3 main.cpp)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( Boletin1P3 ${OpenCV_LIBS} )