#ifndef PLUGINSYSTEM_IPLUGINMANAGER_H
#define PLUGINSYSTEM_IPLUGINMANAGER_H

#include <IPlugin.h>
#include <string>
#include <memory>

class IPluginManager {
public:
  virtual void registerHook(std::shared_ptr<IPlugin> plugin, const PluginHook& hook) = 0;
  virtual void registerFilter(std::shared_ptr<IPlugin> plugin, const PluginFilter& filter) = 0;
  virtual void executeHook(const PluginHook& hook, void* param) = 0;
  virtual void* executeFilter(const PluginFilter& filter, void* param) = 0;
};

#endif //PLUGINSYSTEM_IPLUGINMANAGER_H
