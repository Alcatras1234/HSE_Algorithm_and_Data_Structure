cmake_minimum_required(VERSION 3.27)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled main.cpp
        string_quickSort.h
        string_mergeSort.h
        string_radix_sort.h
        string_radix_sort2.h)
