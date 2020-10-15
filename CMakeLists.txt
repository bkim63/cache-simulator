cmake_minimum_required(VERSION 3.15)
project(Assignment3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(
        cache.h
        cacheblock.cpp
        cacheblock.h
        cacheconfig.cpp
        cacheconfig.h
        main.cpp
        Makefile
        memory.cpp
        memory.h
        README.txt counter.h utils.h utils.cpp counter.cpp cachesimulator.cpp cachesimulator.h cache.cpp)
