#ifndef MORTIFIED_GAME_OBJECT_HPP
#define MORTIFIED_GAME_OBJECT_HPP

#include <list>
#include <utility>
#include <rapidxml.hpp>
#include <boost/shared_ptr.hpp>

namespace mortified {
    class Game;
    class GraphicsComponent;
    class PhysicsComponent;
    
    class GameObject {
    public:
        virtual ~GameObject()
        { }
        
        virtual Game *game() = 0;
        virtual Game const *game() const = 0;

        virtual void load(rapidxml::xml_node<> *node) = 0;
        virtual void save(rapidxml::xml_node<> *parent) = 0;

        virtual PhysicsComponent *physicsComponent() = 0;
        virtual PhysicsComponent const *physicsComponent() const = 0;

        virtual GraphicsComponent *graphicsComponent() = 0;
        virtual GraphicsComponent const *graphicsComponent() const = 0;
    };
}

#endif
