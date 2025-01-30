#ifndef PLUGINSYSTEM_PLUGINLOADER_H
#define PLUGINSYSTEM_PLUGINLOADER_H

#include <IPluginLoader.h>
#include <IPluginManager.h>
#include <memory>
#include <map>

class PluginLoader: public IPluginLoader {
public:
  explicit PluginLoader(std::shared_ptr<IPluginManager> pluginManager);
  ~PluginLoader();

  PluginLoader(PluginLoader&) = delete;
  PluginLoader(PluginLoader&&) = delete;
  void operator=(PluginLoader&) = delete;
  void operator=(PluginLoader&&) = delete;

  void findPlugins(std::string path) override;
  void loadPlugins(std::function<bool(IPlugin *)>) override;
  virtual void unloadPlugins() override;
private:
  std::shared_ptr<IPlugin> loadPlugin(const std::string& path);

  std::vector<std::shared_ptr<IPlugin>> m_items;
  std::shared_ptr<IPluginManager> m_pluginManager;
};

#endif //PLUGINSYSTEM_PLUGINLOADER_H
