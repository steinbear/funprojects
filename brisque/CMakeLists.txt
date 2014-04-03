cmake_minimum_required(VERSION 2.8)
project(brisquefeat )

find_package( OpenCV 2.4.5 REQUIRED )
include_directories ( ${OpenCV_INCLUDE_DIRS} )
link_directories ("/usr/lib")
add_definitions(-DGCC_COMPILER=1)
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
SET(CMAKE_CXX_FLAGS -fpermissive)

add_executable( brisquefeat main.cpp brisque.cpp)

target_link_libraries( brisquefeat ${OpenCV_LIBS} opencv_videostab)

