#ifndef PLUGIN_SYSTEM_DEFINITIONS_H
#define PLUGIN_SYSTEM_DEFINITIONS_H

#ifdef MAKEDLL
#  define API_INF_EXPORT __declspec(dllexport)
#else
#  define API_INF_EXPORT __declspec(dllimport)
#endif

enum PluginType {
  All = 0,
  Translator = 1000,
  Extender
};

enum PluginHook {
  HookNone = 0,
  HookPrintMainMenu = 1000,
  HookTranslationMenu
};

enum PluginFilter {
  FilterNone = 0,
  FilterTranslate = 1000
};

#endif //PLUGIN_SYSTEM_DEFINITIONS_H
