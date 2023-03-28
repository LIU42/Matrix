cmake_minimum_required(VERSION 3.0.0)
project(Matrix VERSION 0.1.0)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

file(GLOB SOURCES_FILES
    ${PROJECT_SOURCE_DIR}/*.c
)
add_executable(Matrix ${SOURCES_FILES})
target_link_libraries(Matrix ${CURSES_LIBRARY})
