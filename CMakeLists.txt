cmake_minimum_required(VERSION 3.07)
project(iceprog-rpispi)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        iceprog.c
        rpispi.c)

add_executable(iceprog-rpispi ${SOURCE_FILES})
target_link_libraries(iceprog-rpispi wiringPi)
install(TARGETS iceprog-rpispi DESTINATION bin)
