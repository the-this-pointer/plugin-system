#include <PluginLoader.h>
#include <IPluginFactory.h>
#include <PluginExceptions.h>

typedef IPluginFactory* (__cdecl *procCreatePlugin)();

auto HInstanceDeleter = [](HINSTANCE hInstance) {
  if (hInstance) {
    FreeLibrary(hInstance);
  }
};

void PluginLoader::loadPlugin(const std::string& path) {
  HINSTANCE pHinstance = LoadLibrary(path.c_str());
  if (!pHinstance) {
    throw PluginLoadException();
  }

  auto createFunc = reinterpret_cast<procCreatePlugin>(
      ::GetProcAddress(pHinstance, "CreatePlugin"));
  if (!createFunc)
  {
    FreeLibrary(pHinstance);
    throw PluginNoFactoryException();
  }

  auto instance = std::shared_ptr<void>(pHinstance, HInstanceDeleter);
  auto pluginFactory = createFunc();
  m_factories[pluginFactory->name()] = std::shared_ptr<IPluginFactory>(pluginFactory, [instance](IPluginFactory* p){
    p->destroy();
    (void)instance;
  });
}