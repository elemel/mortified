#ifndef MORTIFIED_ACTOR_HPP
#define MORTIFIED_ACTOR_HPP

#include <list>
#include <utility>
#include <rapidxml.hpp>

namespace mortified {
    class Game;
    class ControlComponent;
    class GraphicsComponent;
    class PhysicsComponent;
    class PropertyComponent;
    
    class Actor {
    public:
        virtual ~Actor()
        { }

        virtual char const *name() const = 0;

        virtual Game *game() = 0;
        virtual Game const *game() const = 0;

        virtual void load(rapidxml::xml_node<> *node) = 0;
        virtual void save(rapidxml::xml_node<> *parent) = 0;

        virtual PropertyComponent *propertyComponent() = 0;
        virtual PropertyComponent const *propertyComponent() const = 0;

        virtual ControlComponent *controlComponent() = 0;
        virtual ControlComponent const *controlComponent() const = 0;

        virtual PhysicsComponent *physicsComponent() = 0;
        virtual PhysicsComponent const *physicsComponent() const = 0;

        virtual GraphicsComponent *graphicsComponent() = 0;
        virtual GraphicsComponent const *graphicsComponent() const = 0;
    };
}

#endif
