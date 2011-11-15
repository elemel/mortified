#ifndef MORTIFIED_DEFAULT_RENDER_COMPONENT_HPP
#define MORTIFIED_DEFAULT_RENDER_COMPONENT_HPP

#include <memory>

namespace mortified {
    class Actor;
    class RenderComponent;

    std::auto_ptr<RenderComponent> createRenderComponent(Actor *actor);
}

#endif
