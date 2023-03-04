cmake_minimum_required(VERSION 3.22)
project(Lab5array)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab5array
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h
        SMIterator.cpp
        SMIterator.h
        SortedMap.cpp
        SortedMap.h)
