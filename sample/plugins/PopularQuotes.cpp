#include <IPlugin.h>
#include <IPluginManager.h>
#include <definitions.h>
#include <exceptions.h>
#include <iostream>
#include <map>

#define MAJOR_VER "1"
#define MINOR_VER "0"

static std::map<PluginParam, std::string> pluginInfo = {
    {PARAM_NAME,      "Popular Quotes Plugin"},
    {PARAM_VER,       std::string{MAJOR_VER} + "." + std::string{MINOR_VER}},
    {PARAM_DATE,      std::string{__DATE__} + " - " + std::string{__TIME__}},
    {PARAM_MAIN_MENU, "true"}
};

class PopularQuotes {
public:
  static void addMenus(std::vector<std::string>& menus) {
    menus.emplace_back("Print something good");
  }

  static void execMenu(const std::string& menu) {
    // TODO refactor and use action id (menu or toolbar)
    if (menu == "Print something good") {
      std::cout << "Plugin menu selected!" << std::endl;
    }
  }
};

class API_INF_EXPORT PopularQuotesPlugin: public IPlugin {
public:
  PopularQuotesPlugin() {
    std::cout << ">> PopularQuotesPlugin constructor" << std::endl;
  }

  ~PopularQuotesPlugin() {
    std::cout << ">> PopularQuotesPlugin destructor" << std::endl;
  }

  std::vector<PluginType> getType() override {
    return { PluginType::TY_EXTENSION };
  }

  std::vector<PluginHook> registeredHooks() override {
    return { HookMainMenu, HookExecMenu };
  }

  std::vector<PluginFilter> registeredFilters() override {
    return {};
  }

  bool execHook(const PluginHook& hook, void *param) override {
    switch (hook) {
      case HookMainMenu: {
        std::vector<std::string>& menus = *reinterpret_cast<std::vector<std::string>*>(param);
        PopularQuotes::addMenus(menus);
        break;
      }
      case HookExecMenu: {
        std::string& menu = *reinterpret_cast<std::string*>(param);
        PopularQuotes::execMenu(menu);
        break;
      }
      default:
        throw PluginNoHookException();
    }
    return false;
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
};

extern "C" __declspec(dllexport) IPlugin* __cdecl createPlugin()
{
  return new PopularQuotesPlugin;
}