#ifndef PLUGINSYSTEM_PLUGINLOADER_H
#define PLUGINSYSTEM_PLUGINLOADER_H

#include <IContainer.h>
#include <IPluginManager.h>
#include <memory>
#include <map>

class PluginManager: public IPluginManager {
public:
  explicit PluginManager(std::string path);
  ~PluginManager();

  PluginManager(PluginManager&) = delete;
  PluginManager(PluginManager&&) = delete;
  void operator=(PluginManager&) = delete;
  void operator=(PluginManager&&) = delete;

  void setContainer(std::shared_ptr<IContainer> container);

  std::shared_ptr<IContainer> getContainer() override;
  void registerHook(std::shared_ptr<IPlugin> plugin, const PluginHook& hook) override;
  void registerFilter(std::shared_ptr<IPlugin> plugin, const PluginFilter& filter) override;
  void executeHook(const PluginHook &hook, void* param) override;
  void* executeFilter(const PluginFilter &filter, void* param) override;
  void loadPlugins() override;

  std::vector<std::shared_ptr<IPlugin>> pluginsByType(const PluginType& type);
private:

  std::string m_path;
  std::shared_ptr<IContainer> m_container;
  // TODO refactor and move these items to container
  std::vector<std::shared_ptr<IPlugin>> m_plugins;
  std::vector<std::pair<std::shared_ptr<IPlugin>, PluginHook>> m_hooks;
  std::vector<std::pair<std::shared_ptr<IPlugin>, PluginFilter>> m_filters;
};

#endif //PLUGINSYSTEM_PLUGINLOADER_H
