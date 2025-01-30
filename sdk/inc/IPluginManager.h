#ifndef PLUGINSYSTEM_ICONTAINER_H
#define PLUGINSYSTEM_ICONTAINER_H

#include <memory>
#include <vector>
#include "IPlugin.h"

class IPluginManager {
public:
  virtual ~IPluginManager() = default;

  virtual void add(std::shared_ptr<IPlugin> item) = 0;
  virtual void remove(std::shared_ptr<IPlugin> item) = 0;
  [[nodiscard]] virtual std::vector<std::shared_ptr<IPlugin>> getAll() const = 0;
  virtual void removeAll() = 0;
};

#endif //PLUGINSYSTEM_ICONTAINER_H
