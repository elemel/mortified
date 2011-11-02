#ifndef MORTIFIED_DEFAULT_CONTROL_COMPONENT_HPP
#define MORTIFIED_DEFAULT_CONTROL_COMPONENT_HPP

#include <memory>

namespace mortified {
    class Actor;
    class ControlComponent;
    
    std::auto_ptr<ControlComponent> createControlComponent(Actor *actor);
}

#endif
