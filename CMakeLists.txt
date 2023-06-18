cmake_minimum_required(VERSION 3.10)

project(snake)

add_executable(snake snake.cpp)

target_link_libraries(snake PUBLIC SDL2 GL)
