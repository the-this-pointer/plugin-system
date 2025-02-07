#ifndef DOKAN_IPLUGINFACTORY_H
#define DOKAN_IPLUGINFACTORY_H

#include "IPlugin.h"
#include <vector>
#include <string>

class IPluginFactory {
public:
  virtual ~IPluginFactory() = default;

  virtual std::string name() = 0;
  virtual std::string version() = 0;
  virtual std::string author() = 0;
  virtual std::vector<std::string> getDependencies() = 0;

  virtual std::vector<IPlugin*> createPlugins() = 0;

  virtual void destroy() {
    delete this;
  };
};

#endif //DOKAN_IPLUGINFACTORY_H
