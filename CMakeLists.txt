cmake_minimum_required(VERSION 3.12)
project(libhbp_cpp)

set(CMAKE_CXX_STANDARD 11)

add_compile_options("-Wall"
                    "-Wpedantic"
                    "-Wextra"
                    "-fms-extensions"
                    "-Wshadow"
                    "-Wnon-virtual-dtor"
                    "-Wold-style-cast"
                    "-Wcast-align"
                    "-Wunused"
                    "-Woverloaded-virtual"
                    "-Wsign-conversion"
                    "-Wdouble-promotion"
                    "-Wformat=2"
                    "-Wlogical-op"
                    "-Wconversion"
                    "-Werror"
                    "-Woverflow")

if(NOT EXISTS $ENV{EXTOLL_R2_HOME})
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
    include/extoll/rf_definitions.h
    include/extoll/hicann.h
    include/extoll/jtag_definitions.h
    include/extoll/utility/rng.h
    include/extoll/notification_poller.h)


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
    src/notification_poller.cpp)

set(TESTS
    tests/helper/util.h
    tests/helper/util.cpp
    tests/rra.cpp
    tests/jtag.cpp
    tests/if.cpp
    tests/rf_definitions.cpp
    tests/highspeed.cpp
    tests/slowspeed.cpp
    tests/fpga.cpp
    tests/helper/application_protocol.h
    tests/helper/application_protocol.cpp
    tests/anything_unused.cpp)

add_executable(scratch scratch.cpp)
target_include_directories(scratch PRIVATE include)
target_include_directories(scratch PRIVATE ${RMA_INCLUDE})

add_library(rma SHARED ${HEADERS} ${SOURCES})
target_include_directories(rma PRIVATE include)
target_include_directories(rma PRIVATE ${RMA_INCLUDE})
target_link_libraries(rma ${LIBRMARC})
target_link_libraries(rma ${LIBRMA})
target_link_libraries(rma dl)
target_link_libraries(rma pthread)

add_executable(tests tests/run.cpp ${TESTS} ${HEADERS})
target_include_directories(tests PRIVATE include)
target_include_directories(tests PUBLIC external)
target_include_directories(tests PRIVATE ${RMA_INCLUDE})
target_link_libraries(tests ${LIBRMARC})
target_link_libraries(tests ${LIBRMA})
target_link_libraries(tests dl)
target_link_libraries(tests rma)
target_link_libraries(tests pthread)

add_executable(main src/main.cpp ${HEADERS})
target_include_directories(main PRIVATE include)
target_include_directories(main PRIVATE ${RMA_INCLUDE})
target_link_libraries(main ${LIBRMARC})
target_link_libraries(main ${LIBRMA})
target_link_libraries(main dl)
target_link_libraries(main rma)

add_executable(minimal src/minimal.cpp ${HEADERS})
target_include_directories(minimal PRIVATE include)
target_include_directories(minimal PRIVATE ${RMA_INCLUDE})
target_link_libraries(minimal ${LIBRMARC})
target_link_libraries(minimal ${LIBRMA})
target_link_libraries(minimal dl)
target_link_libraries(minimal rma)

add_executable(al src/al.cpp ${HEADERS})
target_include_directories(al PRIVATE include)
target_include_directories(al PRIVATE ${RMA_INCLUDE})
target_link_libraries(al ${LIBRMARC})
target_link_libraries(al ${LIBRMA})
target_link_libraries(al dl)
target_link_libraries(al rma)

add_executable(kill src/kill.cpp)
target_include_directories(kill PRIVATE ${RMA_INCLUDE})
target_link_libraries(kill ${LIBRMA})

add_subdirectory(external/pybind11)
pybind11_add_module(pyhbp EXCLUDE_FROM_ALL python/pyhbp.cpp)
add_custom_command(TARGET pyhbp POST_BUILD COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/python/tests.py ${CMAKE_CURRENT_BINARY_DIR}/test_python_bindings.py )
target_include_directories(pyhbp PRIVATE include)
target_include_directories(pyhbp PRIVATE ${RMA_INCLUDE})
target_link_libraries(pyhbp PRIVATE ${LIBRMARC})
target_link_libraries(pyhbp PRIVATE ${LIBRMA})
target_link_libraries(pyhbp PRIVATE dl)
target_link_libraries(pyhbp PRIVATE rma)
