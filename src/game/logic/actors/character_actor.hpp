#ifndef MORTIFIED_CHARACTER_ACTOR_HPP
#define MORTIFIED_CHARACTER_ACTOR_HPP

#include "actor.hpp"

namespace mortified {
    class UpdateHandler;

    class CharacterControls {
    public:
        bool up;
        bool left;
        bool down;
        bool right;
        bool jump;
        bool fire;

        CharacterControls();
    };

    inline CharacterControls::CharacterControls() :
        up(false),
        left(false),
        down(false),
        right(false),
        jump(false),
        fire(false)
    { }

    class CharacterSensors {
    public:
        bool ceiling;
        bool leftWall;
        bool floor;
        bool rightWall;

        CharacterSensors();
    };

    inline CharacterSensors::CharacterSensors() :
        ceiling(false),
        leftWall(false),
        floor(false),
        rightWall(false)
    { }

    class CharacterSettings {
    public:
        float walkVelocity;
        float jumpVelocity;
        float boostAcceleration;
        float boostDuration;
        float fallVelocity;
        float driftAcceleration;
        float driftVelocity;

        CharacterSettings();
    };

    inline CharacterSettings::CharacterSettings() :
        walkVelocity(0.0f),
        jumpVelocity(0.0f),
        boostAcceleration(0.0f),
        boostDuration(0.0f),
        fallVelocity(0.0f),
        driftAcceleration(0.0f),
        driftVelocity(0.0f)
    { }

    class CharacterActor : public virtual Actor {
    public:
        virtual CharacterSettings const *settings() const = 0;
        virtual CharacterSensors const *sensors() const = 0;
        virtual CharacterControls const *controls() const = 0;
        virtual void controls(CharacterControls const *controls) = 0;

        virtual Vector2 velocity() const = 0;
        virtual void velocity(Vector2 velocity) = 0;

        virtual void wheelMotorEnabled(bool enabled) = 0;
        virtual void wheelMotorVelocity(float velocity) = 0;
        virtual void wheelVelocity(float velocity) = 0;

        virtual void updateHandler(UpdateHandler *handler) = 0;

        virtual float jumpTime() const = 0;
        virtual void jumpTime(float time) = 0;

        virtual bool boost() const = 0;
        virtual void boost(bool boost) = 0;
    };
}

#endif
