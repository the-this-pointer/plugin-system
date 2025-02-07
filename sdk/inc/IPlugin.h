#ifndef PLUGINSYSTEM_IPLUGIN_H
#define PLUGINSYSTEM_IPLUGIN_H

#include <string>
#include <vector>
#include <memory>

class IPlugin: public std::enable_shared_from_this<IPlugin> {
public:
  virtual ~IPlugin() = default;

  bool init() {
    m_loaded = lfLoaded();

    return m_loaded;
  }

  void initComplete() {
    lfAllLoaded();
  }

  virtual void destroy() {
    if (m_loaded)
      lfBeforeUnload();
    delete this;
  };

protected:
  virtual bool lfLoaded() { return true; };
  virtual void lfAllLoaded() {};
  virtual void lfBeforeUnload() {};

private:
  bool m_loaded {false};
};

#endif //PLUGINSYSTEM_IPLUGIN_H
