cmake_minimum_required(VERSION 3.16)
project(GLSLPluginInterface VERSION 1.0.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Interface library (header-only)
add_library(GLSLPluginInterface INTERFACE)

# Include directories
target_include_directories(GLSLPluginInterface INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Add src directory for plugin implementations
target_include_directories(GLSLPluginInterface INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

# Export the target
install(TARGETS GLSLPluginInterface
    EXPORT GLSLPluginInterfaceTargets
    INCLUDES DESTINATION include
)

# Install headers
install(DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

install(DIRECTORY src/
    DESTINATION include/glsl-plugin-interface
    FILES_MATCHING PATTERN "*.h"
)

# Export configuration
install(EXPORT GLSLPluginInterfaceTargets
    FILE GLSLPluginInterfaceTargets.cmake
    NAMESPACE GLSLPluginInterface::
    DESTINATION lib/cmake/GLSLPluginInterface
)

# Create config file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    GLSLPluginInterfaceConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/GLSLPluginInterfaceConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/GLSLPluginInterfaceConfig.cmake
    INSTALL_DESTINATION lib/cmake/GLSLPluginInterface
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/GLSLPluginInterfaceConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/GLSLPluginInterfaceConfigVersion.cmake
    DESTINATION lib/cmake/GLSLPluginInterface
)
