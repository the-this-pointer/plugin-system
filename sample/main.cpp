#include <iostream>
#include <vector>
#include <iomanip>
#include <PluginManager.h>

#define PLUGIN_PATH "plugins"

static bool bRun = true;
std::unique_ptr<PluginManager> pluginManager;

typedef struct {
  std::string caption;
  void (*method)();
} MenuItem;

void printPluginInfo();
void printTranslationMenu();
void exitFromApp();

std::vector<MenuItem> engMenus;
static std::vector<MenuItem> menus {
    {"Loaded Plugins Info", printPluginInfo},
    {"Translation", printTranslationMenu},
};

void printPluginInfo() {
  system("cls");
  _sleep(50);
  auto plugins = pluginManager->pluginsByType(PluginType::All);
  int i = 0;
  for(const auto& plugin: plugins) {
    std::string* nameParam = (std::string*)plugin->getParam("name");
    std::string name = *nameParam;

    std::string* verParam = (std::string*)plugin->getParam("ver");
    std::string ver = *verParam;

    std::string* dateParam = (std::string*)plugin->getParam("date");
    std::string date = *dateParam;

    delete nameParam;
    delete verParam;
    delete dateParam;

    std::cout << ++i << " - Name: " << std::quoted(name) << ", Version: " << std::quoted(ver) <<
      ", Build data: " << std::quoted(date) << std::endl;
  }
  plugins.clear();
  system("pause");
}

void printTranslationMenu() {
  system("cls");
  _sleep(50);

  auto translators = pluginManager->pluginsByType(PluginType::Translator);
  int i = 0;
  std::map<std::string, std::shared_ptr<IPlugin>> langs;
  std::vector<std::string> langMenu;
  for(const auto& translator: translators) {
    std::string* langParam = (std::string*)translator->getParam("lang");
    std::string lang = *langParam;
    std::cout << ++i << " - " << lang << std::endl;
    langMenu.emplace_back(lang);
    langs[lang] = translator;
    delete langParam;
  }
  translators.clear();
  std::cout << ++i << " - " << "English" << std::endl;

  menus = engMenus;
  int usersChoice = 0;
  std::cin >> usersChoice;
  if (usersChoice > langs.size() + 1) {
    std::cout << "Invalid menu selected, fallback to english!" << std::endl;
  } else if (usersChoice <= langs.size()) {
    for (auto& elem: menus) {
      langs[langMenu[usersChoice-1]]->execFilter(FilterTranslate, &elem.caption);
    }
    std::cout << "Translate success!" << std::endl;
  }
  system("pause");
}

void exitFromApp() {
  bRun = false;
}

int main()
{
  pluginManager = std::make_unique<PluginManager>(PLUGIN_PATH);

  menus.emplace_back(MenuItem{"Exit", exitFromApp});
  engMenus = menus;

  do {
    int usersChoice;
    int i = 0;
    for(const auto& menu: menus) {
      std::cout << ++i << " - " << menu.caption << std::endl;
    }

    std::cin >> usersChoice;
    if (usersChoice > menus.size()) {
      std::cout << "Invalid menu selected!" << std::endl;
      system("pause");
      continue;
    }

    menus[usersChoice-1].method();
  } while (bRun);

  return 0;
}