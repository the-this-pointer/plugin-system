#include <Container.h>
#include "exceptions.h"

void Container::registerItem(unsigned int identifier, std::shared_ptr<IPluginHolder> item) {
  if (m_items.count(identifier))
    throw ContainerItemExists(identifier);

  m_items[identifier] = item;
}

std::shared_ptr<IPluginHolder> Container::getItem(unsigned int identifier) {
  if (m_items.count(identifier) == 0)
    throw ContainerItemDoesntExist(identifier);

  return m_items[identifier];
}

// TODO implement onchange item mediator
void Container::removeItem(unsigned int identifier) {
  if (m_items.count(identifier) == 0)
    throw ContainerItemDoesntExist(identifier);

  m_items.erase(identifier);
}

bool Container::hasItem(unsigned int identifier) {
  return m_items.count(identifier) > 0;
}

void Container::clear() {
  m_items.clear();
}
