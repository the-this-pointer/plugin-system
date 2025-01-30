#ifndef PLUGIN_SYSTEM_PLUGINBASE_H
#define PLUGIN_SYSTEM_PLUGINBASE_H

#include <string>
#include <utility>
#include <Windows.h>
#include <IPlugin.h>
#include "definitions.h"

typedef IPlugin* (__cdecl *procCreatePlugin)();

class PluginBase: public IPlugin {
public:
  explicit PluginBase(std::string path);

  ~PluginBase() override;
  PluginBase(PluginBase&) = delete;
  PluginBase(PluginBase&&) = delete;
  void operator=(PluginBase&) = delete;
  void operator=(PluginBase&&) = delete;

  void *getParam(PluginParam param) override;
  bool setParam(PluginParam param, void *value) override;

  virtual void destroy() override;

  virtual void Init() {};
  virtual void lfAllLoaded() {};
  virtual void lfBeforeUnload() {};
private:
  std::string m_path;
  HINSTANCE m_plugin;
  std::shared_ptr<IPlugin> m_instance;
};

#endif //PLUGIN_SYSTEM_PLUGINBASE_H
