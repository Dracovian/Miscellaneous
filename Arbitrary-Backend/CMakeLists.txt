cmake_minimum_required(VERSION 3.00)
project(LinkCrypt LANGUAGES C)
set(CMAKE_C_STANDARD 11)

set(PROJECT_VERSION_MAJOR "1")
set(PROJECT_VERSION_MINOR "0")
set(PROJECT_VERSION_PATCH "1")

set(PKG_CONFIG_EXECUTABLE "/usr/share/pkgconfig")
find_path(GMP_INCLUDE_DIR NAMES gmp.h)
find_library(GMP_LIBRARIES NAMES gmp libgmp)

find_package(PackageHandleStandardArgs)
find_package_handle_standard_args(GMP DEFAULT_MSG GMP_INCLUDE_DIR GMP_LIBRARIES)
mark_as_advanced(GMP_INCLUDE_DIR GMP_LIBRARIES)

set(INCDIR ${PROJECT_SOURCE_DIR}/include)
file(GLOB_RECURSE SRCDIR source/*.c)
include_directories(${INCDIR} ${GMP_INCLUDE_DIR})

configure_file(config.h.in ${INCDIR}/config.h)
add_executable(${PROJECT_NAME} ${SRCDIR})
target_link_libraries(${PROJECT_NAME} ${GMP_LIBRARIES})