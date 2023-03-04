cmake_minimum_required(VERSION 3.20)
project(Lab2DSA)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab2DSA App.cpp
        ExtendedTest.h
        ExtendedTest.cpp
        ShortTest.h
        ShortTest.cpp
        ListIterator.cpp
        ListIterator.h
        IndexedList.cpp
        IndexedList.h)
