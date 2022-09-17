#include <PluginBase.h>
#include <exceptions.h>

PluginBase::PluginBase(std::string path) : m_path(std::move(path))
{
  m_plugin = LoadLibrary(m_path.c_str());
  if (!m_plugin) {
    throw PluginLoadException();
  }

  auto createFunc = reinterpret_cast<procCreatePlugin>(
      ::GetProcAddress(m_plugin, "createPlugin"));
  if (!createFunc)
  {
    FreeLibrary(m_plugin);
    throw PluginNoFactoryException();
  }

  m_instance = createFunc();
}

PluginBase::~PluginBase() {
  if (m_instance)
    m_instance->destroy();
  FreeLibrary(m_plugin);
}

std::vector<PluginType> PluginBase::getType() {
  return m_instance->getType();
}

std::vector<PluginHook> PluginBase::registeredHooks() {
  return m_instance->registeredHooks();
}

std::vector<PluginFilter> PluginBase::registeredFilters() {
  return m_instance->registeredFilters();
}

bool PluginBase::execHook(const PluginHook& hook, void *param) {
  return m_instance->execHook(hook, param);
}

void *PluginBase::execFilter(const PluginFilter& filter, void *param) {
  return m_instance->execFilter(filter, param);
}

void *PluginBase::getParam(const std::string &param) {
  return m_instance->getParam(param);
}

bool PluginBase::setParam(const std::string &param, void *value) {
  return m_instance->setParam(param, value);
}

void PluginBase::destroy() { /* Do nothing here! */ }
