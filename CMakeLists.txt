cmake_minimum_required(VERSION 3.10)
project(find42 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(find42
        fringe.c
        fringe.h
        search.c
        state.h)
