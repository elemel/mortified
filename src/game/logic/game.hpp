#ifndef MORTIFIED_GAME_HPP
#define MORTIFIED_GAME_HPP

#include <Box2D/Box2D.h>

#include <list>
#include <memory>
#include <utility>
#include <boost/shared_ptr.hpp>

namespace mortified {
    class GameObject;
    class GraphicsService;
    class PhysicsService;

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

        virtual float time() const = 0;

        virtual void update(float dt) = 0;

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
