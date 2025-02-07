#ifndef PLUGIN_SYSTEM_DEFINITIONS_H
#define PLUGIN_SYSTEM_DEFINITIONS_H

#ifdef API_PLUGIN_MAKE_DLL
#  define API_PLUGIN_SYS_EXPORT __declspec(dllexport)
#else
#  define API_PLUGIN_SYS_EXPORT __declspec(dllimport)
#endif

#endif //PLUGIN_SYSTEM_DEFINITIONS_H
