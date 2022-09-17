#ifndef PLUGINSYSTEM_PLUGINLOADER_H
#define PLUGINSYSTEM_PLUGINLOADER_H

#include <IPluginManager.h>
#include <memory>
#include <map>

class PluginManager: public IPluginManager {
public:
  PluginManager(std::string path);
  ~PluginManager() = default;

  PluginManager(PluginManager&) = delete;
  PluginManager(PluginManager&&) = delete;
  void operator=(PluginManager&) = delete;
  void operator=(PluginManager&&) = delete;

  void registerHook(std::shared_ptr<IPlugin> plugin, const PluginHook& hook) override;
  void registerFilter(std::shared_ptr<IPlugin> plugin, const PluginFilter& filter) override;
  void executeHook(const PluginHook &hook, void* param) override;
  void* executeFilter(const PluginFilter &filter, void* param) override;

  std::vector<std::shared_ptr<IPlugin>> pluginsByType(const PluginType& type);
private:
  void loadPlugins();

  std::string m_path;
  std::vector<std::shared_ptr<IPlugin>> m_plugins;
  std::vector<std::pair<std::shared_ptr<IPlugin>, PluginHook>> m_hooks;
  std::vector<std::pair<std::shared_ptr<IPlugin>, PluginFilter>> m_filters;
};

#endif //PLUGINSYSTEM_PLUGINLOADER_H
