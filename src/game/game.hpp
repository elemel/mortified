#ifndef MORTIFIED_GAME_HPP
#define MORTIFIED_GAME_HPP

#include <Box2D/Box2D.h>

#include <list>
#include <memory>
#include <utility>
#include <rapidxml.hpp>
#include <boost/shared_ptr.hpp>

namespace mortified {
    class Actor;
    class ControlService;
    class GraphicsService;
    class PhysicsService;
    class PropertyService;

    class Game {
    public:
        typedef boost::shared_ptr<Actor> ActorPtr;
        typedef std::list<ActorPtr> ActorList;
        typedef ActorList::iterator ActorIterator;
        typedef ActorList::const_iterator ConstActorIterator;
        typedef std::pair<ActorIterator, ActorIterator> ActorRange;
        typedef std::pair<ConstActorIterator, ConstActorIterator>
            ConstActorRange;
        
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
        
        virtual ActorRange actors() = 0;
        virtual ConstActorRange actors() const = 0;

        virtual ActorIterator addActor(ActorPtr actor) = 0;
        virtual void removeActor(ActorIterator actor) = 0;

        virtual ActorPtr findActor(char const *name) = 0;
    };
}

#endif
