#ifndef PLUGINSYSTEM_ICONTAINER_H
#define PLUGINSYSTEM_ICONTAINER_H

#include <memory>
#include <IPlugin.h>

class IContainer {
public:
  virtual void registerItem(unsigned int identifier, std::shared_ptr<IPluginHolder> item) = 0;
  virtual std::shared_ptr<IPluginHolder> getItem(unsigned int identifier) = 0;
  virtual void removeItem(unsigned int identifier) = 0;
  virtual bool hasItem(unsigned int identifier) = 0;
  virtual void clear() = 0;
};

#endif //PLUGINSYSTEM_ICONTAINER_H
