cmake_minimum_required(VERSION 3.15.2 FATAL_ERROR)

project(main LANGUAGES CXX VERSION 0.1.0)

find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
    PRIVATE Threads::Threads)
