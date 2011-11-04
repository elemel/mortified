#ifndef MORTIFIED_PHYSICS_DRAW_HPP
#define MORTIFIED_PHYSICS_DRAW_HPP

#include <memory>
#include <Box2D/Box2D.h>

namespace mortified {
    std::auto_ptr<b2Draw> createPhysicsDraw();
}

#endif
