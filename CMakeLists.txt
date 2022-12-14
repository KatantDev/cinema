cmake_minimum_required(VERSION 3.23)
project(cinema C)

set(CMAKE_C_STANDARD 99)

include(FindPythonInterp)
enable_testing()

add_executable(cinema main.c)

add_test(
        NAME films-txt
        COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.py
        WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
)