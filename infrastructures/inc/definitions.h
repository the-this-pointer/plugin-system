#ifndef PLUGIN_SYSTEM_DEFINITIONS_H
#define PLUGIN_SYSTEM_DEFINITIONS_H

#ifdef MAKEDLL
#  define API_INF_EXPORT __declspec(dllexport)
#else
#  define API_INF_EXPORT __declspec(dllimport)
#endif

typedef enum {
  PARAM_NAME,
  PARAM_VER,
  PARAM_DATE,
  PARAM_LANG,
  PARAM_CONTAINER,
  PARAM_USER = 1000,
  PARAM_MAIN_MENU,
} PluginParam;

typedef enum {
  CID_CONSOLE,
  CID_UUSER = 1000
} ContainerId;

typedef enum {
  TY_ALL = 0,
  TY_TRANSLATOR = 1000,
  TY_EXTENSION
} PluginType;

enum PluginHook {
  HookNone = 0,
  HookInjectContainer,
  HookUser = 1000,
  HookMainMenu,
  HookExecMenu,
  HookTranslationMenu
};

enum PluginFilter {
  FilterNone = 0,
  FilterUser = 1000,
  FilterTranslate
};

#endif //PLUGIN_SYSTEM_DEFINITIONS_H
