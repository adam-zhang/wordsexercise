cmake_minimum_required(VERSION 3.5)
project(wordscount)
add_definitions(-W -Wall -std=c++11)

set(sources main.cpp)
add_executable(${PROJECT_NAME} ${sources})