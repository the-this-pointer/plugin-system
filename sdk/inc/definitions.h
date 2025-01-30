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
  PARAM_USER = 1000,
} PluginParam;

#endif //PLUGIN_SYSTEM_DEFINITIONS_H
