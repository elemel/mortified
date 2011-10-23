#ifndef MORTIFIED_GRAPHICS_COMPONENT_HPP
#define MORTIFIED_GRAPHICS_COMPONENT_HPP

#include "component.hpp"

namespace mortified {
    class GraphicsComponent : public virtual Component {
    public:
        virtual void draw() = 0;
    };
}

#endif
