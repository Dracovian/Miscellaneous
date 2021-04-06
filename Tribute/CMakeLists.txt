cmake_minimum_required(VERSION 3.00)
project(Tribute C)
include(FindPkgConfig)

file(GLOB_RECURSE SRC ${PROJECT_SOURCE_DIR}/src/*.c)

set(CMAKE_C_STANDARD 11)
add_executable(Tribute main.c ${SRC})

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED sdl2_image)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
link_libraries(${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} m)