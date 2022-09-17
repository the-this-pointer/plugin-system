#ifndef PLUGIN_SYSTEM_PLUGINBASE_H
#define PLUGIN_SYSTEM_PLUGINBASE_H

#include <string>
#include <utility>
#include <Windows.h>
#include <IPlugin.h>
#include <IPluginManager.h>
#include "definitions.h"

typedef IPlugin* (__cdecl *procCreatePlugin)();

class PluginBase: public IPlugin {
public:
  explicit PluginBase(std::string path);

  ~PluginBase();;
  PluginBase(PluginBase&) = delete;
  PluginBase(PluginBase&&) = delete;
  void operator=(PluginBase&) = delete;
  void operator=(PluginBase&&) = delete;

  std::vector<PluginType> getType() override;
  std::vector<PluginHook> registeredHooks() override;
  std::vector<PluginFilter> registeredFilters() override;
  bool execHook(const PluginHook& hook, void *param) override;
  void *execFilter(const PluginFilter& filter, void *param) override;
  void *getParam(const std::string &param) override;
  bool setParam(const std::string &param, void *value) override;
  void destroy() override;

private:
  std::string m_path;
  HINSTANCE m_plugin;
  IPlugin* m_instance;
};

#endif //PLUGIN_SYSTEM_PLUGINBASE_H
