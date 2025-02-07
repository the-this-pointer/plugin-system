#include <IPlugin.h>
#include <IConsole.h>
#include <PluginApi.h>
#include <PluginExceptions.h>
#include <iostream>
#include <map>

#define MAJOR_VER "1"
#define MINOR_VER "0"

static std::map<PluginParam, std::string> pluginInfo = {
    {PARAM_NAME,      "Standard Console Plugin"},
    {PARAM_VER,       std::string{MAJOR_VER} + "." + std::string{MINOR_VER}},
    {PARAM_DATE,      std::string{__DATE__} + " - " + std::string{__TIME__}},
    {PARAM_CONTAINER, std::to_string(CID_CONSOLE)}
};

class API_INF_EXPORT StdConsolePlugin: public IConsolePlugin {
public:
  StdConsolePlugin() {
    std::cout << ">> StdConsolePlugin constructor" << std::endl;
  }

  ~StdConsolePlugin() {
    std::cout << ">> StdConsolePlugin destructor" << std::endl;
  }

  std::vector<PluginType> getType() override {
    return { PluginType::TY_EXTENSION };
  }

  std::vector<PluginHook> registeredHooks() override {
    return { HookInjectContainer };
  }

  std::vector<PluginFilter> registeredFilters() override {
    return {};
  }

  bool execHook(const PluginHook& hook, void *param) override {
    throw PluginNoHookException();
  }

  void *execFilter(const PluginFilter& filter, void *param) override {
    throw PluginNoFilterException();
  }

  void *getParam(PluginParam param) override {
    if (pluginInfo.count(param))
      return new std::string {pluginInfo[param]};

    return nullptr;
  }

  bool setParam(PluginParam param, void *value) override {
    return false;
  }

  void destroy() override {
    delete this;
  }

  int getUserChoice() override {
    int usersChoice;
    std::cin >> usersChoice;
    return usersChoice;
  }

  void printLine(const std::string &str) override {
    std::cout << str << std::endl;
  }

  void clear() override {
    system("cls");
  }

  void pressAnyKey() override {
    system("pause");
  }
};

extern "C" __declspec(dllexport) IPlugin* __cdecl createPlugin()
{
  return new StdConsolePlugin;
}