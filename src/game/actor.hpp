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

        virtual char const *getName() const = 0;

        virtual Game *getGame() = 0;
        virtual Game const *getGame() const = 0;

        virtual void load(rapidxml::xml_node<> *node) = 0;
        virtual void save(rapidxml::xml_node<> *parent) = 0;

        virtual PropertyComponent *getPropertyComponent() = 0;
        virtual PropertyComponent const *getPropertyComponent() const = 0;

        virtual ControlComponent *getControlComponent() = 0;
        virtual ControlComponent const *getControlComponent() const = 0;

        virtual PhysicsComponent *getPhysicsComponent() = 0;
        virtual PhysicsComponent const *getPhysicsComponent() const = 0;

        virtual GraphicsComponent *getGraphicsComponent() = 0;
        virtual GraphicsComponent const *getGraphicsComponent() const = 0;
    };
}

#endif
