cmake_minimum_required(VERSION 3.16)
project(GLSLPluginInterface)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Interface library (header-only)
add_library(GLSLPluginInterface INTERFACE)

# Include directories
target_include_directories(GLSLPluginInterface INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)