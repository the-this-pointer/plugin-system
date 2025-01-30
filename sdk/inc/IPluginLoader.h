#ifndef PLUGINSYSTEM_IPLUGINMANAGER_H
#define PLUGINSYSTEM_IPLUGINMANAGER_H

#include "IPlugin.h"
#include <string>
#include <memory>
#include <functional>

class IPluginLoader {
public:
  virtual void findPlugins(std::string path) = 0;
  virtual void loadPlugins(std::function<bool(IPlugin *)> loadFunction) = 0;
  virtual void unloadPlugins() = 0;
};

#endif //PLUGINSYSTEM_IPLUGINMANAGER_H
