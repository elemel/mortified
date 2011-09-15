#ifndef MORTIFIED_GAME_LOGIC_HPP
#define MORTIFIED_GAME_LOGIC_HPP

#include <Box2D/Box2D.h>

#include <memory>

namespace mortified {
    class Actor;
    class CharacterActor;

    class GameLogic {
    public:
        virtual ~GameLogic()
        { }

        virtual float time() const = 0;

        virtual b2World *world() = 0;

        virtual void update(float dt) = 0;

        virtual void addActor(std::auto_ptr<Actor> actor) = 0;
        virtual std::auto_ptr<Actor> removeActor(Actor *actor) = 0;

        virtual CharacterActor *hero() = 0;
        virtual void hero(CharacterActor *hero) = 0;
    };
}

#endif
