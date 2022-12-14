cmake_minimum_required(VERSION 3.23)
project(cinema C)

set(CMAKE_C_STANDARD 99)

set (CMAKE_FIND_FRAMEWORK NEVER)
find_package(Python3)
enable_testing()

add_executable(cinema main.c)

add_test(
        NAME films-txt
        COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.py
        WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
)