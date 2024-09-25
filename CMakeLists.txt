cmake_minimum_required(VERSION 3.20)
project(TextRenderer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES 
    src/main.cpp
)
include_directories(SOURCES)

add_executable(TextRenderer ${SOURCES})