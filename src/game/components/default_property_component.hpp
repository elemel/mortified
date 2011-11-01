#ifndef MORTIFIED_DEFAULT_PROPERTY_COMPONENT_HPP
#define MORTIFIED_DEFAULT_PROPERTY_COMPONENT_HPP

#include <memory>

namespace mortified {
    class GameObject;
    class PropertyComponent;

    std::auto_ptr<PropertyComponent> createPropertyComponent(GameObject *object);
}

#endif
