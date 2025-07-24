# GLSL Plugin Interface

A common interface library for GLSL shader library plugins.

## Overview

This library provides a standardized interface for creating and managing GLSL shader library plugins. It includes:

- Common data structures (`GLSLFunction`, `FunctionOverload`, `PluginInfo`)
- Plugin interface (`IPluginInterface`)
- Base implementation class (`BasePluginImpl`)
- C-style plugin loading interface

## Usage

### For Plugin Developers

Include this repository as a git submodule in your plugin project:

```bash
git submodule add <this-repo-url> glsl-plugin-interface
```

### For Application Developers

Include this repository as a git submodule in your main application:

```bash
git submodule add <this-repo-url> glsl-plugin-interface
```

## Building

This is a header-only library. Simply include the headers in your project:

```cmake
add_subdirectory(glsl-plugin-interface)
target_link_libraries(your_target GLSLPluginInterface)
```

## Plugin Development

1. Include the interface: `#include "glsl-plugin-interface/src/BasePluginImpl.h"`
2. Inherit from `BasePluginImpl`
3. Implement the C interface functions
4. Build as a shared library (.so)

## Architecture

```
Main Application                    Plugin (.so)
├── PluginManager              ←→   ├── PluginImpl (inherits BasePluginImpl)
├── glsl-plugin-interface/     ←→   ├── glsl-plugin-interface/ (submodule)
│   ├── IPluginInterface            │   ├── IPluginInterface
│   ├── GLSLTypes                   │   ├── GLSLTypes  
│   └── BasePluginImpl              │   └── BasePluginImpl
└── Application Logic               └── Generated Plugin Data
```

## API Documentation

See individual header files for detailed API documentation.
