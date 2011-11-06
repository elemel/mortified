#ifndef MORTIFIED_GAME_HPP
#define MORTIFIED_GAME_HPP

#include <Box2D/Box2D.h>

#include <list>
#include <memory>
#include <utility>
#include <rapidxml.hpp>

namespace mortified {
    class Actor;
    class ControlService;
    class GraphicsService;
    class PhysicsService;
    class PropertyService;

    class Game {
    public:
        virtual ~Game()
        { }

        virtual void load(char const *file) = 0;
        virtual void save(char const *file) = 0;

        virtual float time() const = 0;

        virtual void update(float dt) = 0;

        virtual PropertyService *propertyService() = 0;
        virtual PropertyService const *propertyService() const = 0;

        virtual ControlService *controlService() = 0;
        virtual ControlService const *controlService() const = 0;

        virtual PhysicsService *physicsService() = 0;
        virtual PhysicsService const *physicsService() const = 0;
        
        virtual GraphicsService *graphicsService() = 0;
        virtual GraphicsService const *graphicsService() const = 0;
        
        virtual Actor *findActor(char const *name) = 0;
        virtual Actor const *findActor(char const *name) const = 0;
    };
}

#endif
