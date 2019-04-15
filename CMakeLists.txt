cmake_minimum_required(VERSION 3.12)
project(mychap C)

add_compile_options(-Wall -Wextra)

include_directories(include)

file(GLOB_RECURSE sources src/*.c)
add_executable(client ${sources})
target_link_libraries(client)
