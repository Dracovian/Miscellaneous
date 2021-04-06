cmake_minimum_required(VERSION 3.00)
project(APIproto C)

# Setting up project variables
set(P ${PROJECT_NAME})
set(CMAKE_C_STANDARD 11)

# Setting up project directory definitions (shorthand)
set(INC ${PROJECT_SOURCE_DIR}/inc)
set(CFG ${INC}/cfg)
set(EXT ${INC}/ext)
set(NET ${INC}/net)

# Recursively listing the file contents of INC
file(GLOB_RECURSE SRC ${INC}/*.c)

# Adding files to be compiled into the executable
add_executable(${P} main.c ${SRC})

# Setting up any compiler definitions used in the sources
# target_compile_definitions(${P} PRIVATE JSON_PARENT_LINKS=1)

# Linking necessary libraries such as OpenSSL and POSIX threads
target_link_libraries(${P} pthread ssl crypto)
