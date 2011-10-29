#ifndef MORTIFIED_DEFAULT_GRAPHICS_COMPONENT_HPP
#define MORTIFIED_DEFAULT_GRAPHICS_COMPONENT_HPP

#include <memory>

namespace mortified {
    class GameObject;
    class GraphicsComponent;

    std::auto_ptr<GraphicsComponent>
    createGraphicsComponent(GameObject *object);
}

#endif
