#ifndef MORTIFIED_DEFAULT_CONTROL_COMPONENT_HPP
#define MORTIFIED_DEFAULT_CONTROL_COMPONENT_HPP

#include <memory>

namespace mortified {
    class ControlComponent;
    class GameObject;
    
    std::auto_ptr<ControlComponent> createControlComponent(GameObject *object);
}

#endif
