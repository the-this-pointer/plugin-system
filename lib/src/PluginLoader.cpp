#include <PluginLoader.h>
#include <PluginExceptions.h>
#include <iostream>
#include <algorithm>
#include <utility>
#include <filesystem>
#include <windows.h>
#include <vector>

namespace fs = std::filesystem;

PluginLoader::PluginLoader(std::shared_ptr<IPluginManager> pluginManager): m_pluginManager(pluginManager) {
}

PluginLoader::~PluginLoader() {
}

void PluginLoader::findPlugins(std::string path) {
  // iterate through files and load dlls
  for (const auto & file : fs::directory_iterator(path)) {
    const fs::path& path = file.path();
    if (path.string().find(".dll") != path.string().size()-4)
      continue;

    try {
      loadPlugin(path.string());
    }
    catch (std::exception& ex) {
      std::cout << "Exception occured during load plugin: " << ex.what() << std::endl;
    }
  }
}

void PluginLoader::loadPlugins(std::function<bool(IPluginFactory *)> loadDecision) {

  std::map<std::string, std::vector<std::string>> dependencyGraph;
  for(const auto& factory: m_factories) {
    dependencyGraph[factory.first] = factory.second->getDependencies();
  }

  std::vector<std::string> sortedDeps = topologicalSort(dependencyGraph);
  std::vector<std::string> loadedDeps;
  for (const auto& factoryName : sortedDeps) {
    if (!loadDecision(m_factories[factoryName].get())) {
      continue;
    }

    if(!isSubset(loadedDeps, m_factories[factoryName]->getDependencies())) {
      // TODO warn user
      continue;
    }

    auto plugins = m_factories[factoryName]->createPlugins();
    for(auto& pluginPtr: plugins) {
      auto plugin = std::shared_ptr<IPlugin>(pluginPtr, [factory = m_factories[factoryName]](IPlugin* p){
        p->destroy();
        (void)factory;
      });

      m_plugins.push_back(plugin);
      m_pluginManager->add(plugin);
      plugin->init();
    }

    loadedDeps.push_back(factoryName);
  }

  for(const auto& component: m_pluginManager->getAll()) {
    component->initComplete();
  }
}

void PluginLoader::unloadPlugins() {
  m_pluginManager->removeAll();
  m_plugins.clear();
  m_factories.clear();
}

std::vector<std::string> PluginLoader::topologicalSort(const std::map<std::string, std::vector<std::string>>& dependencyGraph) {
  std::vector<std::string> sortedPlugins;
  std::map<std::string, bool> visited;

  std::function<void(const std::string&)> visit = [&](const std::string& plugin) {
    if (!visited[plugin]) {
      visited[plugin] = true;
      for (const auto& dep : dependencyGraph.at(plugin)) {
        visit(dep);
      }
      sortedPlugins.push_back(plugin);
    }
  };

  for (const auto& [plugin, _] : dependencyGraph) {
    visit(plugin);
  }

  return sortedPlugins;
}

bool PluginLoader::isSubset(const std::vector<std::string> set, const std::vector<std::string> subset) {
  std::vector<std::string> sortedSubset = subset;
  std::vector<std::string> sortedSet = set;

  std::sort(sortedSubset.begin(), sortedSubset.end());
  std::sort(sortedSet.begin(), sortedSet.end());

  return std::includes(sortedSet.begin(), sortedSet.end(), sortedSubset.begin(), sortedSubset.end());
}
