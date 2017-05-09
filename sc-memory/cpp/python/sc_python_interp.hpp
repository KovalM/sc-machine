#pragma once

#include "../sc_utils.hpp"
#include "../sc_types.hpp"
#include "../utils/sc_lock.hpp"

#include <string>
#include <memory>

namespace py
{

class ScPythonBridgeImpl;

class ScPythonBridge
{
public:
  
  _SC_EXTERN ScPythonBridge();
  _SC_EXTERN ~ScPythonBridge();

  _SC_EXTERN MemoryBufferSafePtr SendEvent(std::string const & eventName, MemoryBufferSafePtr data);
  ScPythonBridgeImpl * GetImpl() const;
  
private:
  ScPythonBridgeImpl * m_impl;
};

SHARED_PTR_TYPE(ScPythonBridge)

class ScPythonInterpreter
{
public:
  _SC_EXTERN static bool Initialize(std::string const & name);
  _SC_EXTERN static void Shutdown();

  /* This function runs specified script. Path to script should be relative to 
   * python.modules_path config value.
   * This function is a thread safe
   */
  _SC_EXTERN static void RunScript(std::string const & scriptName, ScPythonBridgePtr bridge = ScPythonBridgePtr());

  _SC_EXTERN static void AddModulesPath(std::string const & modulesPath);

protected:
  static void CollectModules(StringVector const & modulePath);
  static void CollectModulesInPath(std::string const & path);

private:
  static bool ms_isInitialized;
  static std::wstring ms_name;
  static utils::ScLock m_lock;

  using ModulesMap = std::unordered_map<std::string, std::string>;
  static ModulesMap ms_foundModules;
  
  using ModulePathSet = std::set<std::string>;
  static ModulePathSet ms_modulePaths;
};

} // py