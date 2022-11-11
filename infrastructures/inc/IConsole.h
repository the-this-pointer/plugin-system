#ifndef PLUGINSYSTEM_ICONSOLE_H
#define PLUGINSYSTEM_ICONSOLE_H

#include <string>

class IConsole {
public:
  virtual int  getUserChoice() = 0;
  virtual void printLine(const std::string& str) = 0;
  virtual void clear() = 0;
  virtual void pressAnyKey() = 0;
};

class IConsolePlugin: public IPlugin, public IConsole {};

#endif //PLUGINSYSTEM_ICONSOLE_H
