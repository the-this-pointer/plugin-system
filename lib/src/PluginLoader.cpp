#include <PluginLoader.h>
#include <PluginBase.h>
#include <exceptions.h>
#include <iostream>
#include <algorithm>
#include <utility>
#include <filesystem>

namespace fs = std::filesystem;

PluginLoader::PluginLoader(std::shared_ptr<IPluginManager> pluginManager): m_pluginManager(pluginManager) {
}

PluginLoader::~PluginLoader() {}

void PluginLoader::findPlugins(std::string path) {
  // iterate through files and load dlls
  for (const auto & file : fs::directory_iterator(path)) {
    const fs::path& path = file.path();
    if (path.string().find(".dll") == std::string::npos)
      continue;

    try {
      std::shared_ptr<IPlugin> plugin = std::make_shared<PluginBase>(path.string());
      m_items.push_back(plugin);
    }
    catch (std::exception& ex) {
      std::cout << "Exception occured during load plugin: " << ex.what() << std::endl;
    }
  }
}

void PluginLoader::loadPlugins(std::function<bool(IPlugin *)> examineFunction) {
  for(const auto& component: m_items) {
    if (examineFunction(component.get()))
      m_pluginManager->add(component);
  }
}
void PluginLoader::unloadPlugins() {
  m_pluginManager->removeAll();
  m_items.clear();
}