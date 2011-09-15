#ifndef MORTIFIED_ACTOR_HPP
#define MORTIFIED_ACTOR_HPP

#include <Box2D/Box2D.h>

namespace mortified {
    class CharacterActor;
    class GameLogic;
    class Vector2;

    class Actor {
    public:
        virtual ~Actor()
        { }

        virtual GameLogic *gameLogic() = 0;
        virtual GameLogic const *gameLogic() const = 0;

        virtual void create() = 0;
        virtual void destroy() = 0;

        virtual Vector2 position() const = 0;

        virtual void update(float dt) = 0;

        virtual void addContact(b2Contact *contact) = 0;
        virtual void removeContact(b2Contact *contact) = 0;

        virtual CharacterActor *asCharacterActor() = 0;
        virtual CharacterActor const *asCharacterActor() const = 0;
    };
}

#endif
