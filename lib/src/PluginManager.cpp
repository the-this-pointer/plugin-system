#include <PluginManager.h>
#include <algorithm>

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
