#ifndef PLUGINSYSTEM_EXCEPTIONS_H
#define PLUGINSYSTEM_EXCEPTIONS_H

#include <exception>
#include <string>

class PluginException: public std::exception {
public:
  explicit PluginException(std::string msg): m_msg(std::move(msg)) {}

  [[nodiscard]] const char * what () const noexcept final
  {
    return m_msg.c_str();
  }

private:
  std::string m_msg;
};

class PluginLoadException: public PluginException {
public:
  PluginLoadException(): PluginException("Unable to load plugin.") {}
};

class PluginNoFactoryException: public PluginException {
public:
  PluginNoFactoryException(): PluginException("Factory method not found.") {}
};

class PluginNoHookException: public PluginException {
public:
  PluginNoHookException(): PluginException("Hook not found in this plugin.") {}
};

class PluginNoFilterException: public PluginException {
public:
  PluginNoFilterException(): PluginException("Filter not found in this plugin.") {}
};

class ContainerItemExists: public PluginException {
public:
  explicit ContainerItemExists(unsigned int identifier): PluginException("Item exists in container, item id: " + std::to_string(identifier)) {}
};

class ContainerItemDoesntExist: public PluginException {
public:
  explicit ContainerItemDoesntExist(unsigned int identifier): PluginException("Item doesn't exist in container, item id: " + std::to_string(identifier)) {}
};

#endif //PLUGINSYSTEM_EXCEPTIONS_H
