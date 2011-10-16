#ifndef MORTIFIED_PHYSICS_COMPONENT_HPP
#define MORTIFIED_PHYSICS_COMPONENT_HPP

#include "component.hpp"

#include <list>
#include <string>
#include <Box2D/Box2D.h>

namespace mortified {
    class PhysicsComponent : public virtual Component {
    public:
        class BodyData {
        public:
            PhysicsComponent *component;
            b2Body *body;
            std::string name;

            BodyData(PhysicsComponent *component, b2Body *body,
                     std::string name) :
                component(component),
                body(body),
                name(name)
            { }
        };

        class JointData {
        public:
            PhysicsComponent *component;
            b2Joint *joint;
            std::string name;

            JointData(PhysicsComponent *component, b2Joint *joint,
                      std::string name) :
                component(component),
                joint(joint),
                name(name)
            { }
        };

        typedef std::list<BodyData> BodyList;
        typedef BodyList::iterator BodyIterator;

        typedef std::list<JointData> JointList;
        typedef JointList::iterator JointIterator;
    };
}

#endif
