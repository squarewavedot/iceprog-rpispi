cmake_minimum_required(VERSION 3.07)
project(iceprog-rpicsi)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        iceprog.c
        rpispi.c)

add_executable(iceprog-rpicsi ${SOURCE_FILES})
target_link_libraries(iceprog-rpicsi ftdi wiringPi)