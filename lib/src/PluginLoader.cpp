#include <PluginLoader.h>
#include <exceptions.h>
#include <iostream>
#include <algorithm>
#include <utility>
#include <filesystem>
#include <windows.h>

namespace fs = std::filesystem;

typedef IPlugin* (__cdecl *procCreatePlugin)();

PluginLoader::PluginLoader(std::shared_ptr<IPluginManager> pluginManager): m_pluginManager(pluginManager) {
}

PluginLoader::~PluginLoader() {}

void PluginLoader::findPlugins(std::string path) {
  // iterate through files and load dlls
  for (const auto & file : fs::directory_iterator(path)) {
    const fs::path& path = file.path();
    if (path.string().find(".dll") != path.string().size()-4)
      continue;

    try {
      std::shared_ptr<IPlugin> plugin = loadPlugin(path.string());
      if (plugin)
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

std::shared_ptr<IPlugin> PluginLoader::loadPlugin(const std::string& path) {
  HINSTANCE plugin = LoadLibrary(path.c_str());
  if (!plugin) {
    throw PluginLoadException();
  }

  auto createFunc = reinterpret_cast<procCreatePlugin>(
      ::GetProcAddress(plugin, "createPlugin"));
  if (!createFunc)
  {
    FreeLibrary(plugin);
    throw PluginNoFactoryException();
  }

  return std::shared_ptr<IPlugin>(createFunc(), [plugin](IPlugin* p){
    p->destroy();
    delete p;
    FreeLibrary(plugin);
  });
}