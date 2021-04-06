cmake_minimum_required(VERSION 3.00)
project(2FA LANGUAGES CXX)

set(CMAKE_BUILD_TYPE MinSizeRel)
set(CMAKE_CXX_STANDARD 20)
include(FindOpenSSL)

include_directories(${PROJECT_SOURCE_DIR}/include ${OPENSSL_INCLUDE_DIR})
file(GLOB_RECURSE FILES ${PROJECT_SOURCE_DIR}/source/*.cc)

add_executable(${PROJECT_NAME} ${FILES})
target_link_libraries(${PROJECT_NAME} ${OPENSSL_LIBRARIES})
