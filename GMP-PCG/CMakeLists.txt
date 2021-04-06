cmake_minimum_required(VERSION 3.00)
project(BigPCG VERSION "0.1.1")

set(PKG_CONFIG_EXECUTABLE "/usr/share/pkgconfig")
set(CMAKE_CXX_STANDARD 20)

find_path(GMP_INCLUDE_DIR NAMES gmp.h)
find_library(GMP_LIBRARIES NAMES gmp libgmp)

find_package(PackageHandleStandardArgs)
find_package_handle_standard_args(GMP DEFAULT_MSG GMP_INCLUDE_DIR GMP_LIBRARIES)
mark_as_advanced(GMP_INCLUDE_DIR GMP_LIBRARIES)

include_directories(${GMP_INCLUDE_DIR})
add_executable(${PROJECT_NAME} entry.cc inc/gmppcg.hh)
target_link_libraries(${PROJECT_NAME} ${GMP_LIBRARIES})