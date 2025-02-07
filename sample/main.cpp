#include <iostream>
#include <vector>
#include <iomanip>
#include <PluginLoader.h>
#include <PluginManager.h>
#include <IConsole.h>
#include "PluginExceptions.h"

#define PLUGIN_PATH "plugins"

static bool bRun = true;
std::unique_ptr<PluginManager> pluginManager;

typedef struct {
  std::string caption;
  void (*method)(const std::shared_ptr<IConsole>& console);
  std::shared_ptr<IPlugin> plugin;
} MenuItem;

void printPluginInfo(const std::shared_ptr<IConsole>& console);
void printTranslationMenu(const std::shared_ptr<IConsole>& console);
void exitFromApp(const std::shared_ptr<IConsole>& console);

std::vector<MenuItem> engMenus;
static std::vector<MenuItem> menus {
    {"Loaded Plugins Info", printPluginInfo, nullptr},
    {"Translation", printTranslationMenu, nullptr},
};

void printPluginInfo(const std::shared_ptr<IConsole>& console) {
  console->clear();
  _sleep(50);
  auto plugins = pluginManager->pluginsByType(PluginType::TY_ALL);
  int i = 0;
  for(const auto& plugin: plugins) {
    auto* nameParam = (std::string*)plugin->getParam(PARAM_NAME);
    std::string name = *nameParam;

    auto* verParam = (std::string*)plugin->getParam(PARAM_VER);
    std::string ver = *verParam;

    auto* dateParam = (std::string*)plugin->getParam(PARAM_DATE);
    std::string date = *dateParam;

    delete nameParam;
    delete verParam;
    delete dateParam;

    console->printLine(std::to_string(++i).append(" - Name: '").append(name).append("', Version: '").append(ver)
                .append("', Build data: '").append(date).append("'"));
  }
  plugins.clear();
  console->pressAnyKey();
}

void printTranslationMenu(const std::shared_ptr<IConsole>& console) {
  console->clear();
  _sleep(50);

  auto translators = pluginManager->pluginsByType(PluginType::TY_TRANSLATOR);
  int i = 0;
  std::map<std::string, std::shared_ptr<IPlugin>> langs;
  std::vector<std::string> langMenu;
  for(const auto& translator: translators) {
    auto* langParam = (std::string*)translator->getParam(PARAM_LANG);
    std::string lang = *langParam;
    console->printLine(std::to_string(++i).append(" - ").append(lang));
    langMenu.emplace_back(lang);
    langs[lang] = translator;
    delete langParam;
  }
  translators.clear();
  console->printLine(std::to_string(++i).append(" - English"));

  menus = engMenus;
  int usersChoice = console->getUserChoice();
  if (usersChoice > langs.size() + 1) {
    console->printLine("Invalid menu selected, fallback to english!");
  } else if (usersChoice <= langs.size()) {
    for (auto& elem: menus) {
      langs[langMenu[usersChoice-1]]->execFilter(FilterTranslate, &elem.caption);
    }
    console->printLine("Translate success!");
  }
  console->pressAnyKey();
}

void exitFromApp(const std::shared_ptr<IConsole>& console) {
  bRun = false;
  console->printLine("Exiting from app...");
}

int main()
{
  pluginManager = std::make_unique<PluginManager>(PLUGIN_PATH);
  pluginManager->setContainer(std::make_shared<PluginManager>()->instance());
  pluginManager->loadPlugins();

  std::shared_ptr<IConsole> console = nullptr;
  
  try {
    auto plugin = pluginManager->getContainer()->getItem(CID_CONSOLE);
    console = std::dynamic_pointer_cast<IConsole>(plugin->instance());
  } catch (ContainerItemDoesntExist& e) {
    std::cout << "Unable to get console, what: " << e.what() << std::endl;
    return 1;
  }

  auto pluginsWithMenu = pluginManager->pluginsByType(PluginType::TY_EXTENSION);
  for(auto& plugin: pluginsWithMenu) {
    auto* param = (std::string*)plugin->getParam(PARAM_MAIN_MENU);
    if (param) {
      std::vector<std::string> menuList;
      plugin->execHook(HookMainMenu, &menuList);
      for (const auto& menu: menuList) {
        menus.emplace_back(MenuItem{menu, nullptr, plugin});
      }
      delete param;
    }
  }

  menus.emplace_back(MenuItem{"Exit", exitFromApp, nullptr});
  engMenus = menus;

  do {
    int i = 0;
    for(const auto& menu: menus) {
      console->printLine(std::to_string(++i) + " - " + menu.caption);
    }

    int usersChoice = console->getUserChoice();
    if (usersChoice > menus.size()) {
      console->printLine("Invalid menu selected!");
      console->pressAnyKey();
      continue;
    }

    if (menus[usersChoice-1].method)
      menus[usersChoice-1].method(console);
    else if (menus[usersChoice-1].plugin)
      menus[usersChoice-1].plugin->execHook(HookExecMenu, &menus[usersChoice-1].caption);
  } while (bRun);

  return 0;
}