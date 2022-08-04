cmake_minimum_required(VERSION 3.0.0)
project(Matrix VERSION 0.1.0)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(Matrix main.c matrix.c matrix.h config.h)
target_link_libraries(Matrix ${CURSES_LIBRARY})
