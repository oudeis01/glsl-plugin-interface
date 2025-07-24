#pragma once
#include "GLSLTypes.h"
#include <vector>
#include <string>
#include <map>

/**
 * @brief Common interface for all GLSL shader library plugins
 */
class IPluginInterface {
public:
    virtual ~IPluginInterface() = default;
    
    // Plugin information
    virtual const char* getName() const = 0;
    virtual const char* getVersion() const = 0;
    virtual const char* getAuthor() const = 0;
    
    // Function search (O(1) performance with hash map)
    virtual const GLSLFunction* findFunction(const std::string& name) const = 0;
    virtual std::vector<std::string> getAllFunctionNames() const = 0;
    virtual size_t getFunctionCount() const = 0;
    
    // Category-based search
    virtual std::vector<std::string> getFunctionsByCategory(const std::string& category) const = 0;
    virtual std::vector<std::string> getAvailableCategories() const = 0;
    
    // Advanced queries
    virtual std::vector<const GLSLFunction*> findFunctionsByReturnType(const std::string& returnType) const = 0;
    virtual std::vector<const GLSLFunction*> findFunctionsByParameterCount(size_t paramCount) const = 0;
};

// C interface for plugin loading (prevents symbol mangling)
extern "C" {
    /**
     * @brief Create a plugin instance
     * @return Pointer to plugin interface, or nullptr on failure
     */
    IPluginInterface* createPlugin();
    
    /**
     * @brief Destroy a plugin instance
     * @param plugin Plugin instance to destroy
     */
    void destroyPlugin(IPluginInterface* plugin);
    
    /**
     * @brief Get plugin information string
     * @return Plugin info in format "name:version:author"
     */
    const char* getPluginInfo();
    
    /**
     * @brief Get plugin ABI version for compatibility checking
     * @return ABI version number
     */
    int getPluginABIVersion();
}

// Plugin ABI version (increment when interface changes)
#define PLUGIN_ABI_VERSION 1
