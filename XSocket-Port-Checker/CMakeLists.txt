cmake_minimum_required(VERSION 3.00)
project(XSocket VERSION "0.1.1")
set(CMAKE_C_STANDARD 11)

string(TIMESTAMP PROJECT_BUILD_DATE "%Y-%m-%d" UTC)
if(CMAKE_SIZEOF_VOID_P LESS 4)
    message(FATAL_ERROR "This program requires an OS that is at least 32-bit or 64-bit.")
endif()

add_executable(${PROJECT_NAME} source/xsocket.c source/entry.c)

if(WIN32)
    add_definitions(-DPLATFORM_WINDOWS)
    target_link_libraries(${PROJECT_NAME} ws2_32 wsock32 pthread)
else()
    add_definitions(-DPLATFORM_POSIX)
    target_link_libraries(${PROJECT_NAME} pthread)
endif()