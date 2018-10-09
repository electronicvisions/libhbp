cmake_minimum_required(VERSION 3.12)
project(libhbp_cpp)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(
        "-Wall" "-Wpedantic" "-Wextra"
)

if (NOT EXISTS $ENV{EXTOLL_R2_HOME})
    message(FATAL_ERROR "$EXTOLL_R2_HOME must be set to a directory!")
endif()

set(RMA_INCLUDE $ENV{EXTOLL_R2_HOME}/include)
set(RMA_LIB $ENV{EXTOLL_R2_HOME}/lib)

find_library(LIBRMA NAMES librma2.so PATHS ${RMA_LIB})
find_library(LIBRMARC NAMES librma2rc.so PATHS ${RMA_LIB})

set(HEADERS
        include/physical_buffer.h
        include/register_file.h
        include/connection.h
        include/helper.h
        include/hbp.h
        include/traits.h
        include/jtag.h
        include/exception.h
        include/fpga.h
        include/register_files.h
        )

set(SOURCES
        src/physical_buffer.cpp
        src/register_file.cpp
        src/register_files.cpp
        src/connection.cpp
        src/hbp.cpp
        src/rma.cpp
        src/jtag.cpp
        src/main.cpp
        src/fpga.cpp
        src/exception.cpp
        )

add_executable(rma ${HEADERS} ${SOURCES})
target_include_directories(rma PRIVATE include)
target_include_directories(rma PRIVATE ${RMA_INCLUDE})
target_link_libraries(rma ${LIBRMARC})
target_link_libraries(rma ${LIBRMA})
target_link_libraries(rma dl)

add_executable(scratch scratch.cpp)
