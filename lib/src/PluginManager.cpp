#include <PluginManager.h>
#include <algorithm>

std::shared_ptr<PluginManager> PluginManager::instance() {
  static std::shared_ptr<PluginManager> ins;
  if (!ins)
    ins = std::make_shared<PluginManager>();
  return ins;
}

void PluginManager::add(std::shared_ptr<IPlugin> item) {
  m_items.push_back(item);
}

std::vector<std::shared_ptr<IPlugin>> PluginManager::getAll() const {
  return m_items;
}

void PluginManager::remove(std::shared_ptr<IPlugin> item) {
  m_items.erase(std::remove(m_items.begin(), m_items.end(), item), m_items.end());
}

void PluginManager::removeAll() {
  m_items.clear();
}
