cmake_minimum_required(VERSION 3.6)
project(FileDBR)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/FdbrDatabase.cpp src/FdbrDatabase.h src/FdbrQueryBuilder.cpp src/FdbrQueryBuilder.h)
add_executable(FileDBR ${SOURCE_FILES})