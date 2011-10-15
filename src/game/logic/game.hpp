#ifndef MORTIFIED_GAME_HPP
#define MORTIFIED_GAME_HPP

#include <Box2D/Box2D.h>

#include <list>
#include <memory>
#include <utility>
#include <boost/shared_ptr.hpp>

namespace mortified {
    class Actor;
    class CharacterActor;
    class GameObject;

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

        virtual b2World *world() = 0;

        virtual void update(float dt) = 0;

        virtual void addActor(std::auto_ptr<Actor> actor) = 0;
        virtual std::auto_ptr<Actor> removeActor(Actor *actor) = 0;

        virtual CharacterActor *hero() = 0;
        virtual void hero(CharacterActor *hero) = 0;

        virtual ObjectRange objects() = 0;
        virtual ConstObjectRange objects() const = 0;

        virtual ObjectIterator addObject(ObjectPtr object) = 0;
        virtual void removeObject(ObjectIterator object) = 0;
    };
}

#endif
