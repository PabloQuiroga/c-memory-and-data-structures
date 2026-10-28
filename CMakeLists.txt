cmake_minimum_required(VERSION 3.20)
project(c_memory_and_data_structures C)

set(CMAKE_C_STANDARD 11)

include_directories(
        src
        src/data_structures
)

add_executable(c_memory_and_data_structures
        src/main.c
        src/data_structures/dynamic_array.c
        src/data_structures/dynamic_array.h
        src/tests.c
        src/data_structures/linked_list.h
        src/data_structures/linked_list.c
        src/data_structures/stack.h
        src/data_structures/stack.c
        src/data_structures/hash_table.h
        src/data_structures/hash_table.c
)
