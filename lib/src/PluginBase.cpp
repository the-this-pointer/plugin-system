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

  m_instance = std::shared_ptr<IPlugin>(createFunc(), [this](IPlugin* p){
    p->destroy();
    FreeLibrary(m_plugin);
  });
}

PluginBase::~PluginBase() = default;

void *PluginBase::getParam(PluginParam param) {
  return m_instance->getParam(param);
}

bool PluginBase::setParam(PluginParam param, void *value) {
  return m_instance->setParam(param, value);
}

void PluginBase::destroy() { /* Do nothing here! */ }
