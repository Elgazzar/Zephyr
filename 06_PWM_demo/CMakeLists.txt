# Minimum CMake version
cmake_minimum_required(VERSION 3.22.0)


#locate the zephyr RTOS source
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

#Name the project
project(button)

#locate the source coide for the application
target_sources(app PRIVATE src/main.c)