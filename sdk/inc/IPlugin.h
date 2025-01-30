#ifndef PLUGINSYSTEM_IPLUGIN_H
#define PLUGINSYSTEM_IPLUGIN_H

#include <string>
#include <vector>
#include <memory>
#include "definitions.h"

class IPlugin: std::enable_shared_from_this<IPlugin> {
public:
  std::shared_ptr<IPlugin> instance()
  {
    return shared_from_this();
  }

  virtual ~IPlugin() = default;

  virtual void* getParam(PluginParam param) = 0;
  virtual bool setParam(PluginParam param, void* value) = 0;

  virtual void destroy() = 0;

  virtual void Init() = 0;

  virtual void lfAllLoaded() = 0;
  virtual void lfBeforeUnload() = 0;
};

#endif //PLUGINSYSTEM_IPLUGIN_H
