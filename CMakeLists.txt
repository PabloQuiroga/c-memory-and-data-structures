cmake_minimum_required(VERSION 4.3)
project(c_memory_and_data_structures C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(c_memory_and_data_structures
        src/main.c
        src/dynamic_array.c
        src/dynamic_array.h
        src/tests.c
        src/linked_list.h
        src/linked_list.c)
