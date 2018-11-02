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
        include/extoll.h
        include/jtag.h
        include/exception.h
        include/fpga.h
        include/register_files.h
        include/hicann.h
        include/jtag_registers.h

        include/utility/rng.h
        include/utility/watch.h

        include/tests/switchram.h
        include/tests/test.h
        include/tests/jtagrw.h
        )

set(SOURCES
        src/physical_buffer.cpp
        src/register_file.cpp
        src/register_files.cpp
        src/connection.cpp
        src/extoll.cpp
        src/rma.cpp
        src/jtag.cpp
        src/fpga.cpp
        src/exception.cpp
        src/hicann.cpp

        src/tests/test.cpp
        src/tests/switchram.cpp
        src/tests/jtagrw.cpp
        )



add_executable(scratch scratch.cpp)


add_library(rma SHARED ${HEADERS} ${SOURCES})
target_include_directories(rma PRIVATE include)
target_include_directories(rma PRIVATE ${RMA_INCLUDE})
target_link_libraries(rma ${LIBRMARC})
target_link_libraries(rma ${LIBRMA})
target_link_libraries(rma dl)

add_executable(tests src/main.cpp ${HEADERS})
target_include_directories(tests PRIVATE include)
target_include_directories(tests PRIVATE ${RMA_INCLUDE})
target_link_libraries(tests ${LIBRMARC})
target_link_libraries(tests ${LIBRMA})
target_link_libraries(tests dl)
target_link_libraries(tests rma)