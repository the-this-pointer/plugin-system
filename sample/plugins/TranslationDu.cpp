#include <IPlugin.h>
#include <IPluginManager.h>
#include <definitions.h>
#include <exceptions.h>
#include <iostream>
#include <map>

#define MAJOR_VER "1"
#define MINOR_VER "0"

static std::map<std::string, std::string> pluginInfo = {
    {"name", "Dutch Translation Plugin"},
    {"ver", std::string{MAJOR_VER} + "." + std::string{MINOR_VER}},
    {"date", std::string{__DATE__} + " - " + std::string{__TIME__}},
    {"lang", "Dutch"},
};

class TranslationDu {
public:
  static void translationMenu(std::vector<std::string>& menus) {
    menus.emplace_back("Dutch Translation");
  }

  static std::string translate(const std::string& input) {
    return "Translated Text!";
  }
};

class API_INF_EXPORT TranslationDuPlugin: public IPlugin {
public:
  TranslationDuPlugin() {
    std::cout << ">> TranslationDuPlugin constructor" << std::endl;
  }

  ~TranslationDuPlugin() {
    std::cout << ">> TranslationDuPlugin destructor" << std::endl;
  }

  std::vector<PluginType> getType() override {
    return { PluginType::TypeTranslator };
  }

  std::vector<PluginHook> registeredHooks() override {
    return { HookTranslationMenu };
  }

  std::vector<PluginFilter> registeredFilters() override {
    return { FilterTranslate };
  }

  bool execHook(const PluginHook& hook, void *param) override {
    switch (hook) {
      case HookTranslationMenu: {
        std::vector<std::string>& menus = *reinterpret_cast<std::vector<std::string>*>(param);
        TranslationDu::translationMenu(menus);
        break;
      }
      default:
        throw PluginNoHookException();
    }
    return false;
  }

  void *execFilter(const PluginFilter& filter, void *param) override {
    switch (filter) {
      case FilterTranslate: {
        std::string& input = *reinterpret_cast<std::string*>(param);
        input = TranslationDu::translate(input);
        return &input;
      }
      default:
        throw PluginNoFilterException();
    }
    return nullptr;
  }

  void *getParam(const std::string &param) override {
    if (pluginInfo.count(param))
      return new std::string {pluginInfo[param]};

    return nullptr;
  }

  bool setParam(const std::string &param, void *value) override {
    return false;
  }

  void destroy() override {
    delete this;
  }
};

extern "C" __declspec(dllexport) IPlugin* __cdecl createPlugin()
{
  return new TranslationDuPlugin;
}