#ifndef MORTIFIED_ACTOR_BASE_HPP
#define MORTIFIED_ACTOR_BASE_HPP

#include "actor.hpp"

namespace mortified {
    class ActorBase : public virtual Actor {
    public:
        explicit ActorBase(GameLogic *logic);

        GameLogic *gameLogic();
        GameLogic const *gameLogic() const;

        void create();
        void destroy();

        Vector2 position() const;

        void update(float dt);

        void addContact(b2Contact *contact);
        void removeContact(b2Contact *contact);

        CharacterActor *asCharacterActor();
        CharacterActor const *asCharacterActor() const;

    protected:
        GameLogic *gameLogic_;
    };
}

#endif
