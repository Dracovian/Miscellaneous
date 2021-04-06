cmake_minimum_required(VERSION 3.00)
project(Discord_Scraper C)

file(GLOB_RECURSE INC ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE SRC ${PROJECT_SOURCE_DIR}/source/*.c)

set(CMAKE_C_STANDARD 11)
add_executable(${PROJECT_NAME} ${SRC} main.c)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} wsock32 ws2_32 pthread ssl)
else()
    target_link_libraries(${PROJECT_NAME} pthread ssl)
endif()