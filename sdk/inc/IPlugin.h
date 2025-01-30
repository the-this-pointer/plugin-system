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

  virtual void* getParam(PluginParam param) { return nullptr; };

  virtual void destroy() {};

  virtual void Init() {};

  virtual void lfAllLoaded() {};
  virtual void lfBeforeUnload() {};
};

#endif //PLUGINSYSTEM_IPLUGIN_H
