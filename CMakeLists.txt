cmake_minimum_required(VERSION 3.5.2)

project(thread_group)
set(CMAKE_CXX_STANDARD 14)

add_executable(
    ${PROJECT_NAME}
    thread_group.hpp
    main.cpp
)
