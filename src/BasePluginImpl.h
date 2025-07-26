#pragma once
#include "../include/IPluginInterface.h"
#include <unordered_map>
#include <algorithm>
#include <set>

/**
 * @brief Base class for implementing GLSL shader library plugins
 * This class provides common functionality that plugins can inherit from
 */
class BasePluginImpl : public IPluginInterface {
protected:
    const PluginInfo& plugin_info;
    const std::vector<GLSLFunction>& functions;
    const std::unordered_map<std::string, const GLSLFunction*>& function_map;
    
public:
    BasePluginImpl(const PluginInfo& info, 
                   const std::vector<GLSLFunction>& funcs,
                   const std::unordered_map<std::string, const GLSLFunction*>& func_map)
        : plugin_info(info), functions(funcs), function_map(func_map) {}
    
    virtual ~BasePluginImpl() = default;
    
    // Plugin information
    const char* getName() const override { 
        return plugin_info.name.c_str(); 
    }
    
    const char* getVersion() const override { 
        return plugin_info.version.c_str(); 
    }
    
    const char* getAuthor() const override { 
        return plugin_info.author.c_str(); 
    }
    
    // Function search (O(1) performance with hash map)
    const GLSLFunction* findFunction(const std::string& name) const override {
        auto it = function_map.find(name);
        return (it != function_map.end()) ? it->second : nullptr;
    }
    
    std::vector<std::string> getAllFunctionNames() const override {
        std::vector<std::string> names;
        names.reserve(functions.size());
        for (const auto& func : functions) {
            names.push_back(func.name);
        }
        return names;
    }
    
    size_t getFunctionCount() const override {
        return functions.size();
    }
    
    // Category-based search (extract from file path)
    std::vector<std::string> getFunctionsByCategory(const std::string& category) const override {
        std::vector<std::string> result;
        for (const auto& func : functions) {
            if (func.filePath.find(category) != std::string::npos) {
                result.push_back(func.name);
            }
        }
        return result;
    }
    
    std::vector<std::string> getAvailableCategories() const override {
        std::set<std::string> categories;
        for (const auto& func : functions) {
            // Extract category from file path (e.g., "lighting/common/ggx.glsl" -> "lighting")
            size_t first_slash = func.filePath.find('/');
            if (first_slash != std::string::npos) {
                categories.insert(func.filePath.substr(0, first_slash));
            }
        }
        return std::vector<std::string>(categories.begin(), categories.end());
    }
    
    // Advanced queries
    std::vector<const GLSLFunction*> findFunctionsByReturnType(const std::string& returnType) const override {
        std::vector<const GLSLFunction*> result;
        for (const auto& func : functions) {
            for (const auto& overload : func.overloads) {
                if (overload.returnType == returnType) {
                    result.push_back(&func);
                    break; // Only add once per function
                }
            }
        }
        return result;
    }
    
    std::vector<const GLSLFunction*> findFunctionsByParameterCount(size_t paramCount) const override {
        std::vector<const GLSLFunction*> result;
        for (const auto& func : functions) {
            for (const auto& overload : func.overloads) {
                if (overload.paramTypes.size() == paramCount) {
                    result.push_back(&func);
                    break; // Only add once per function
                }
            }
        }
        return result;
    }
};
