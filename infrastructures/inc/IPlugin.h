#ifndef PLUGINSYSTEM_IPLUGIN_H
#define PLUGINSYSTEM_IPLUGIN_H

#include <string>
#include <vector>
#include <definitions.h>

typedef void(*HookFunc)(void*);
typedef void*(*FilterFunc)(void*);

class IPlugin {
public:
  virtual std::vector<PluginType> getType() = 0;
  virtual std::vector<PluginHook> registeredHooks() = 0;
  virtual std::vector<PluginFilter> registeredFilters() = 0;
  virtual bool execHook(const PluginHook& hook, void* param) = 0;
  virtual void* execFilter(const PluginFilter& filter, void* param) = 0;
  virtual void* getParam(const std::string& param) = 0;
  virtual bool setParam(const std::string& param, void* value) = 0;
  virtual void destroy() = 0;
};

#endif //PLUGINSYSTEM_IPLUGIN_H
