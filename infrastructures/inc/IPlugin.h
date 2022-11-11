#ifndef PLUGINSYSTEM_IPLUGIN_H
#define PLUGINSYSTEM_IPLUGIN_H

#include <string>
#include <vector>
#include <memory>
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
  virtual void* getParam(PluginParam param) = 0;
  virtual bool setParam(PluginParam param, void* value) = 0;
  virtual void destroy() = 0;
};

class IPluginHolder: public IPlugin {
public:
  virtual std::shared_ptr<IPlugin> instance() = 0;
};

#endif //PLUGINSYSTEM_IPLUGIN_H
