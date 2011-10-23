#ifndef MORTIFIED_DEFAULT_GRAPHICS_COMPONENT_HPP
#define MORTIFIED_DEFAULT_GRAPHICS_COMPONENT_HPP

#include <boost/shared_ptr.hpp>

namespace mortified {
    class GameObject;
    class GraphicsComponent;

    boost::shared_ptr<GraphicsComponent>
    createGraphicsComponent(GameObject *object);
}

#endif
