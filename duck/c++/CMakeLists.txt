cmake_minimum_required(VERSION 3.10)
project(duck)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(SOURCE 
    main.cpp
)

add_executable(duck ${SOURCE})