#ifndef MORTIFIED_PHYSICS_SERVICE_HPP
#define MORTIFIED_PHYSICS_SERVICE_HPP

#include "service.hpp"

#include <Box2D/Box2D.h>

namespace mortified {
    class PhysicsService : public virtual Service {
    public:
        virtual b2World *world() = 0;
        virtual b2World const *world() const = 0;
    };
}

#endif
