#include <PluginManager.h>
#include <PluginBase.h>
#include <exceptions.h>
#include <filesystem>
#include <iostream>
#include <algorithm>
#include <utility>

PluginManager::PluginManager(std::string path) : m_path(std::move(path)) {
  std::cout << ">> PluginManager constructor" << std::endl;
}

PluginManager::~PluginManager() {
  std::cout << ">> PluginManager destructor" << std::endl;
  m_container->clear();
  m_filters.clear();
  m_hooks.clear();
  m_plugins.clear();
}

void PluginManager::loadPlugins() {
  // iterate through files and load dlls
  for (const auto & file : std::filesystem::directory_iterator(m_path)) {
    const std::filesystem::path& path = file.path();
    if (path.string().find(".dll") == std::string::npos)
      continue;

    try {
      std::shared_ptr<IPluginHolder> plugin = std::make_shared<PluginBase>(path.string());

      for (const auto& hook: plugin->registeredHooks()) {
        registerHook(plugin, hook);
        if (hook == HookInjectContainer && m_container)
        {
          auto* containerId = (std::string*)plugin->getParam(PARAM_CONTAINER);
          if (containerId) {
            unsigned int containerIdentifier = std::stoul(*containerId);
            if (!m_container->hasItem(containerIdentifier)) {
              m_container->registerItem(std::stoul(*containerId), plugin);
            } else {
              // TODO add log
            }
            delete containerId;
          }
        }
      }

      for (const auto& filter: plugin->registeredFilters())
        registerFilter(plugin, filter);

      m_plugins.emplace_back(plugin);
    }
    catch (std::exception& ex) {
      std::cout << "Exception occured during load plugin: " << ex.what() << std::endl;
    }
  }
}

std::shared_ptr<IContainer> PluginManager::getContainer() {
  return m_container;
}

void PluginManager::registerHook(std::shared_ptr<IPlugin> plugin, const PluginHook& hook) {
  m_hooks.emplace_back(std::pair<std::shared_ptr<IPlugin>, PluginHook>{plugin, hook});
}

void PluginManager::registerFilter(std::shared_ptr<IPlugin> plugin, const PluginFilter& filter) {
  m_filters.emplace_back(std::pair<std::shared_ptr<IPlugin>, PluginFilter>{plugin, filter});
}

void PluginManager::executeHook(const PluginHook &hook, void* param) {
  for (const auto& elem: m_hooks) {
    try {
      if (elem.second == hook)
        elem.first->execHook(hook, param);
    }
    catch (std::exception& ex) {
      std::cout << "Exception occured during hook execution: " << ex.what() << std::endl;
    }
  }
}

void* PluginManager::executeFilter(const PluginFilter &filter, void* param) {
  for (const auto& elem: m_filters) {
    try {
      if (elem.second == filter)
        elem.first->execFilter(filter, param);
    }
    catch (std::exception& ex) {
      std::cout << "Exception occured during filter execution: " << ex.what() << std::endl;
    }
  }
  return param;
}

std::vector<std::shared_ptr<IPlugin>> PluginManager::pluginsByType(const PluginType &type) {
  if (type == PluginType::TY_ALL)
    return m_plugins;

  std::vector<std::shared_ptr<IPlugin>> res;
  for (const auto& plugin: m_plugins) {
    std::vector<PluginType> types = plugin->getType();
    if (std::count(types.begin(), types.end(), type))
      res.emplace_back(plugin);
  }
  return res;
}

void PluginManager::setContainer(std::shared_ptr<IContainer> container) {
  m_container = std::move(container);
}
