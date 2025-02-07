#ifndef PLUGINSYSTEM_PLUGINLOADER_H
#define PLUGINSYSTEM_PLUGINLOADER_H

#include <IPluginFactory.h>
#include <IPluginLoader.h>
#include <IPluginManager.h>
#include <memory>
#include <map>
#include <string>
#include <vector>
#include <windows.h>

class PluginLoader: public IPluginLoader {
public:
  explicit PluginLoader(std::shared_ptr<IPluginManager> pluginManager);
  ~PluginLoader();

  PluginLoader(PluginLoader&) = delete;
  PluginLoader(PluginLoader&&) = delete;
  void operator=(PluginLoader&) = delete;
  void operator=(PluginLoader&&) = delete;

  void findPlugins(std::string path) override;
  void loadPlugins(std::function<bool(IPluginFactory *)>) override;
  virtual void unloadPlugins() override;
private:
  void loadPlugin(const std::string& path);
  bool isSubset(const std::vector<std::string> set, const std::vector<std::string> subset);
  std::vector<std::string> topologicalSort(const std::map<std::string, std::vector<std::string>>& dependencyGraph);

  std::map<std::string, std::shared_ptr<IPluginFactory>> m_factories;
  std::vector<std::shared_ptr<IPlugin>> m_plugins;
  std::shared_ptr<IPluginManager> m_pluginManager;
};

#endif //PLUGINSYSTEM_PLUGINLOADER_H
