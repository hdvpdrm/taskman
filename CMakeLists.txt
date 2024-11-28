cmake_minimum_required(VERSION 3.10)
project(taskman)
set (CMAKE_C_STANDARD 99)

add_link_options(-lm)

set (SOURCES main.c argparser.c util_functions.c file_utils.c toml.c task.c task_struct.h)
set (HEADERS argparser.h util_functions.h file_utils.h toml.h task.h task_struct.c)

add_executable(taskman ${SOURCES} ${HEADERS})
