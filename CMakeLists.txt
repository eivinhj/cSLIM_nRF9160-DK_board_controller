# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(hello_world)

#add local sources
FILE(GLOB app_sources src/*.c)
target_sources(app PRIVATE ${app_sources})
target_include_directories(app PRIVATE src)

add_subdirectory(src/drivers)
add_subdirectory(src/devices)
add_subdirectory(src/buffers)
add_subdirectory(src/tasks)

target_sources(app PRIVATE src/main.c)
