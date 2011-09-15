#include "actor_base.hpp"

#include "math.hpp"

#include <iostream>

namespace mortified {
    ActorBase::ActorBase(GameLogic *logic) :
        gameLogic_(logic)
    { }

    GameLogic *ActorBase::gameLogic()
    {
        return gameLogic_;
    }

    GameLogic const *ActorBase::gameLogic() const
    {
        return gameLogic_;
    }

    void ActorBase::create()
    { }

    void ActorBase::destroy()
    { }

    Vector2 ActorBase::position() const
    {
        return Vector2();
    }

    void ActorBase::update(float dt)
    {
        (void) dt;
    }

    void ActorBase::addContact(b2Contact *contact)
    {
        (void) contact;
    }

    void ActorBase::removeContact(b2Contact *contact)
    {
        (void) contact;
    }

    CharacterActor *ActorBase::asCharacterActor()
    {
        return 0;
    }

    CharacterActor const *ActorBase::asCharacterActor() const
    {
        return 0;
    }
}
