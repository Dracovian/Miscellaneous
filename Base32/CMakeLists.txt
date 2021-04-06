cmake_minimum_required(VERSION 3.00)
project(base32 C)

file(GLOB_RECURSE B32_INC ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE B32_SRC ${PROJECT_SOURCE_DIR}/src/*.c)

add_library(libbase32 STATIC ${B32_INC})
set_target_properties(libbase32 PROPERTIES LINKER_LANGUAGE C)

add_executable(base32 main.c ${B32_SRC})
target_include_directories(base32 PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(base32 libbase32)