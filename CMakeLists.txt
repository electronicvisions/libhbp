cmake_minimum_required(VERSION 3.12)
project(libhbp_cpp)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(
        "-Wall" "-Wpedantic" "-Wextra" "-fms-extensions"
)

if (NOT EXISTS $ENV{EXTOLL_R2_HOME})
    message(FATAL_ERROR "$EXTOLL_R2_HOME must be set to a directory!")
endif()

set(RMA_INCLUDE $ENV{EXTOLL_R2_HOME}/include)
set(RMA_LIB $ENV{EXTOLL_R2_HOME}/lib)

find_library(LIBRMA NAMES librma2.so PATHS ${RMA_LIB})
find_library(LIBRMARC NAMES librma2rc.so PATHS ${RMA_LIB})

set(HEADERS
    include/extoll/buffer.h
    include/extoll/register_file.h
    include/extoll/connection.h
    include/extoll/helper.h
    include/extoll/extoll.h
    include/extoll/jtag.h
    include/extoll/exception.h
    include/extoll/fpga.h
    include/extoll/hbp_def.h
    include/extoll/hicann.h
    include/extoll/jtag_registers.h

    include/extoll/utility/rng.h
    include/extoll/utility/watch.h
)

set(SOURCES
    src/buffer.cpp
    src/register_file.cpp
    src/connection.cpp
    src/extoll.cpp
    src/rma.cpp
    src/jtag.cpp
    src/fpga.cpp
    src/exception.cpp
    src/hicann.cpp
)

set(TESTS
    tests/util.h
    tests/util.cpp

    tests/rra.cpp
    tests/jtag.cpp
    tests/static.cpp
    tests/hbp_def.cpp
)

add_executable(scratch scratch.cpp)
target_include_directories(scratch PRIVATE include)
target_include_directories(scratch PRIVATE ${RMA_INCLUDE})

add_library(rma SHARED ${HEADERS} ${SOURCES})
target_include_directories(rma PRIVATE include)
target_include_directories(rma PRIVATE ${RMA_INCLUDE})
target_link_libraries(rma ${LIBRMARC})
target_link_libraries(rma ${LIBRMA})
target_link_libraries(rma dl)

add_executable(tests tests/run.cpp ${TESTS} ${HEADERS})
target_include_directories(tests PRIVATE include)
target_include_directories(tests PRIVATE external)
target_include_directories(tests PRIVATE ${RMA_INCLUDE})
target_link_libraries(tests ${LIBRMARC})
target_link_libraries(tests ${LIBRMA})
target_link_libraries(tests dl)
target_link_libraries(tests rma)
