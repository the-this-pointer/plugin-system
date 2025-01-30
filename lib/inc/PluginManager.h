#ifndef PLUGINSYSTEM_CONTAINER_H
#define PLUGINSYSTEM_CONTAINER_H

#include <IPluginManager.h>
#include <map>
#include <utility>
#include <memory>

class PluginManager: public IPluginManager {
public:
  static std::shared_ptr<PluginManager> instance() {
    static std::shared_ptr<PluginManager> ins(new PluginManager);
    return ins;
  }

  void add(std::shared_ptr<IPlugin> item) override;
  void remove(std::shared_ptr<IPlugin> item) override;
  [[nodiscard]] std::vector<std::shared_ptr<IPlugin>> getAll() const override;
  void removeAll() override;

private:
  std::vector<std::shared_ptr<IPlugin>> m_items;
};

namespace Components {
  inline auto addPlugin(std::shared_ptr<IPlugin> object) -> void {
    PluginManager::instance()->add(std::move(object));
  }

  inline auto removePlugin(std::shared_ptr<IPlugin> object) -> void{
    PluginManager::instance()->remove(std::move(object));
  }

  inline auto allObjects() -> std::vector<std::shared_ptr<IPlugin>> {
    return PluginManager::instance()->getAll();
  }

  template<typename T>
  inline auto getObject() -> std::shared_ptr<T> {
    for (auto object : PluginManager::instance()->getAll()) {

      auto castObject = std::dynamic_pointer_cast<T>(object);

      if (castObject)
        return castObject;
    }

    return nullptr;
  }

  template<typename T>
  inline auto getObjects() -> std::vector<std::shared_ptr<T>> {
    std::vector<std::shared_ptr<T>> objectList;

    for (auto object : PluginManager::instance()->getAll()) {

      auto castObject = std::dynamic_pointer_cast<T>(object);

      if (castObject)
        objectList.push_back(castObject);
    }

    return objectList;
  }
}

#endif //PLUGINSYSTEM_CONTAINER_H
