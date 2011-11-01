#ifndef MORTIFIED_GAME_HPP
#define MORTIFIED_GAME_HPP

#include <Box2D/Box2D.h>

#include <list>
#include <memory>
#include <utility>
#include <rapidxml.hpp>
#include <boost/shared_ptr.hpp>

namespace mortified {
    class ControlService;
    class GameObject;
    class GraphicsService;
    class PhysicsService;
    class PropertyService;

    class Game {
    public:
        typedef boost::shared_ptr<GameObject> ObjectPtr;
        typedef std::list<ObjectPtr> ObjectList;
        typedef ObjectList::iterator ObjectIterator;
        typedef ObjectList::const_iterator ConstObjectIterator;
        typedef std::pair<ObjectIterator, ObjectIterator> ObjectRange;
        typedef std::pair<ConstObjectIterator, ConstObjectIterator>
            ConstObjectRange;
        
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
        
        virtual ObjectRange objects() = 0;
        virtual ConstObjectRange objects() const = 0;

        virtual ObjectIterator addObject(ObjectPtr object) = 0;
        virtual void removeObject(ObjectIterator object) = 0;
    };
}

#endif
