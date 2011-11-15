#ifndef MORTIFIED_DEFAULT_PROPERTY_COMPONENT_HPP
#define MORTIFIED_DEFAULT_PROPERTY_COMPONENT_HPP

#include <memory>

namespace mortified {
    class Actor;
    class PropertyComponent;

    std::auto_ptr<PropertyComponent> createPropertyComponent(Actor *actor);
}

#endif
