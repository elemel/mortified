#ifndef MORTIFIED_PHYSICS_SERVICE_HPP
#define MORTIFIED_PHYSICS_SERVICE_HPP

#include "service.hpp"

#include <Box2D/Box2D.h>

namespace mortified {
    class PhysicsService : public virtual Service {
    public:
        virtual b2World *getWorld() = 0;
        virtual b2World const *getWorld() const = 0;
    };
}

#endif
