#ifndef MORTIFIED_GAME_HPP
#define MORTIFIED_GAME_HPP

#include <list>
#include <memory>
#include <utility>
#include <rapidxml.hpp>
#include <Box2D/Box2D.h>

namespace mortified {
    class Actor;
    class ControlService;
    class Matrix3;
    class PhysicsService;
    class PropertyService;
    class RenderService;
    class SoundService;

    class Game {
    public:
        virtual ~Game()
        { }

        virtual void loadConfig(rapidxml::xml_node<> *node) = 0;
        virtual void saveConfig(rapidxml::xml_node<> *parentNode) = 0;
        
        virtual void loadModule(char const *file, Matrix3 parentTransform) = 0;
        virtual void saveModule(char const *file, Matrix3 parentTransform) = 0;

        virtual float getTime() const = 0;

        virtual void update(float dt) = 0;

        virtual PropertyService *getPropertyService() = 0;
        virtual PropertyService const *getPropertyService() const = 0;

        virtual ControlService *getControlService() = 0;
        virtual ControlService const *getControlService() const = 0;

        virtual PhysicsService *getPhysicsService() = 0;
        virtual PhysicsService const *getPhysicsService() const = 0;
        
        virtual RenderService *getRenderService() = 0;
        virtual RenderService const *getRenderService() const = 0;

        virtual SoundService *getSoundService() = 0;
        virtual SoundService const *getSoundService() const = 0;

        virtual Actor *findActor(char const *name) = 0;
        virtual Actor const *findActor(char const *name) const = 0;
    };
}

#endif
