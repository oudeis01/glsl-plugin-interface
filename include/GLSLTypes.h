#pragma once
#include <vector>
#include <string>
#include <initializer_list>

/**
 * @brief Represents a function overload with return type and parameter types
 */
struct FunctionOverload {
    std::string returnType;
    std::vector<std::string> paramTypes;
    
    FunctionOverload(const std::string& ret, const std::vector<std::string>& params)
        : returnType(ret), paramTypes(params) {}
    
    FunctionOverload(const std::string& ret, const std::initializer_list<std::string>& params)
        : returnType(ret), paramTypes(params) {}
};

/**
 * @brief Represents a GLSL function with metadata and overloads
 */
struct GLSLFunction {
    std::string name;
    std::string filePath;
    std::vector<FunctionOverload> overloads;
    
    // Constructor for basic function without overloads
    GLSLFunction(const std::string& n, const std::string& path)
        : name(n), filePath(path) {}
    
    // Constructor with overloads for optimized generation
    GLSLFunction(const std::string& n, const std::string& path, const std::initializer_list<FunctionOverload>& ovl)
        : name(n), filePath(path), overloads(ovl) {}
};

/**
 * @brief Plugin metadata information
 */
struct PluginInfo {
    std::string name;
    std::string version;
    std::string author;
    
    PluginInfo(const std::string& n, const std::string& v, const std::string& a)
        : name(n), version(v), author(a) {}
};
