cmake_minimum_required(VERSION 3.23)
project(cinema C)

set(CMAKE_C_STANDARD 99)

find_package(Python3)
enable_testing()

configure_file(films.txt films.txt COPYONLY)
add_executable(cinema main.c)

message("${PYTHON_FOUND}")
add_test(
        NAME films-txt
        COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.py
        WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
)