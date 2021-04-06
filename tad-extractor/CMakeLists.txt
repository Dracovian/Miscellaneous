cmake_minimum_required(VERSION 3.00)
project(tadextractor LANGUAGES C)
set(CMAKE_C_STANDARD 11)

if(WIN32)
    add_definitions(-DPLATFORM_WIN32)
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC ${PROJECT_SOURCE_DIR}/src/*.c)
add_executable(${PROJECT_NAME} ${SRC})