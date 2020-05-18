cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(boost_tutorial)

message("Entering boost tutorial")

find_package(Boost 1.65 COMPONENTS system program_options signals python REQUIRED)

set(PY_VERSION 2.7)
find_package(PythonLibs ${PY_VERSION} REQUIRED)

add_subdirectory(02_signals_slots)
add_subdirectory(03_python)
