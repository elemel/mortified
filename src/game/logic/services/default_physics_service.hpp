#ifndef MORTIFIED_DEFAULT_PHYSICS_SERVICE_HPP
#define MORTIFIED_DEFAULT_PHYSICS_SERVICE_HPP

#include <memory>

namespace mortified {
    class PhysicsService;
    
    std::auto_ptr<PhysicsService> createPhysicsService();
}

#endif
