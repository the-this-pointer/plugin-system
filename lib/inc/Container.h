#ifndef PLUGINSYSTEM_CONTAINER_H
#define PLUGINSYSTEM_CONTAINER_H

#include <IContainer.h>
#include <map>

class Container: public IContainer {
public:
  static std::shared_ptr<Container> instance() {
    static std::shared_ptr<Container> ins = std::make_shared<Container>();
    return ins;
  }

  void registerItem(unsigned int identifier, std::shared_ptr<IPluginHolder> item) override;
  std::shared_ptr<IPluginHolder> getItem(unsigned int identifier) override;
  void removeItem(unsigned int identifier) override;
  bool hasItem(unsigned int identifier) override;
  void clear() override;

private:
  std::map<unsigned int, std::shared_ptr<IPluginHolder>> m_items;
};

#endif //PLUGINSYSTEM_CONTAINER_H
