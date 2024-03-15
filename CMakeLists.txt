# Project's name
project ( PyPhoenix5 C CXX )

# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.1)

# need this for std::string_view
set(CMAKE_CXX_STANDARD 17)

# target_compile_options(PyPhoenix5 -Wdeprecated-declarations)

if (${CMAKE_LIBRARY_ARCHITECTURE} STREQUAL "arm-linux-gnueabihf") # Jetson TK1 / Pi
    set(PHOENIX_LIBS_DIR ${CMAKE_SOURCE_DIR}/lib/arm32)
elseif (${CMAKE_LIBRARY_ARCHITECTURE} STREQUAL "aarch64-linux-gnu") # Jetson TX2
    set(PHOENIX_LIBS_DIR ${CMAKE_SOURCE_DIR}/lib/arm64)
else()
    set(PHOENIX_LIBS_DIR ${CMAKE_SOURCE_DIR}/lib/x86-64)
endif()

add_subdirectory(pybind11)
pybind11_add_module(PyPhoenix5 PyPhoenix5.cpp)
target_link_libraries(PyPhoenix5 PRIVATE ${PHOENIX_LIBS_DIR}/libCTRE_Phoenix.so)
target_link_libraries(PyPhoenix5 PRIVATE ${PHOENIX_LIBS_DIR}/libCTRE_PhoenixCCI.so)
target_link_libraries(PyPhoenix5 PRIVATE ${PHOENIX_LIBS_DIR}/libCTRE_PhoenixTools.so)

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package (Threads REQUIRED)
find_package(PythonInterp REQUIRED)

# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories(${PYTHON_INCLUDE_DIRS})

add_executable(test_motor ${PROJECT_SOURCE_DIR}/test_motor.cpp)

target_link_libraries(test_motor ${PHOENIX_LIBS_DIR}/libCTRE_Phoenix.so)
target_link_libraries(test_motor ${PHOENIX_LIBS_DIR}/libCTRE_PhoenixCCI.so)
target_link_libraries(test_motor ${PHOENIX_LIBS_DIR}/libCTRE_PhoenixTools.so)
target_link_libraries(test_motor Threads::Threads)

add_custom_command(TARGET test_motor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PHOENIX_LIBS_DIR}
        $<TARGET_FILE_DIR:test_motor>)
