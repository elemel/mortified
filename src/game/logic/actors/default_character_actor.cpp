#include "default_character_actor.hpp"

#include "actor_base.hpp"
#include "character_actor.hpp"
#include "character_stand_state.hpp"
#include "game_logic.hpp"
#include "math.hpp"
#include "physics_user_data.hpp"
#include "state.hpp"
#include "update_handler.hpp"

#include <iostream>
#include <Box2D/Box2D.h>

namespace mortified {
    class DefaultCharacterActor :
        public virtual CharacterActor,
        private virtual ActorBase
    {
    public:
        DefaultCharacterActor(GameLogic *logic, Vector2 position, float radius);

        void create();
        void destroy();

        Vector2 position() const;

        void update(float dt);

        void addContact(b2Contact *contact);
        void removeContact(b2Contact *contact);

        CharacterActor *asCharacterActor();
        CharacterActor const *asCharacterActor() const;

        CharacterSettings const *settings() const;
        CharacterSensors const *sensors() const;
        CharacterControls const *controls() const;
        void controls(CharacterControls const *controls);

        Vector2 velocity() const;
        void velocity(Vector2 velocity);

        void wheelMotorEnabled(bool enabled);
        void wheelMotorVelocity(float velocity);
        void wheelVelocity(float velocity);

        void updateHandler(UpdateHandler *handler);

        float jumpTime() const;
        void jumpTime(float time);

        bool boost() const;
        void boost(bool boost);

    private:
        Vector2 position_;
        float radius_;

        b2Body *mainBody_;
        b2Body *wheelBody_;
        b2RevoluteJoint *wheelJoint_;
        b2Fixture *floorSensorFixture_;
        int floorContactCount_;

        CharacterSettings settings_;
        CharacterSensors sensors_;
        CharacterControls controls_;
        std::auto_ptr<State> state_;
        UpdateHandler *updateHandler_;

        float jumpTime_;
        bool boost_;

        float wheelRadius() const
        {
            return 0.7 * radius_;
        }

        void updateSensors()
        {
            sensors_ = CharacterSensors();
            sensors_.floor = (floorContactCount_ != 0);
        }

        void updateState()
        {
            std::auto_ptr<State> newState = state_->transition();
            if (newState.get()) {
                state_->leave();
                state_ = newState;
                state_->enter();
            }
        }
    };

    DefaultCharacterActor::DefaultCharacterActor(GameLogic *logic,
                                                 Vector2 position,
                                                 float radius)
    :
        ActorBase(logic),
        position_(position),
        radius_(radius),

        mainBody_(0),
        wheelBody_(0),
        wheelJoint_(0),
        floorSensorFixture_(0),
        floorContactCount_(0),
        updateHandler_(0),
        jumpTime_(0.0f),
        boost_(false)
    {
        settings_.walkVelocity = 5.0f;
        settings_.jumpVelocity = 6.0f;
        settings_.boostAcceleration = 9.0f;
        settings_.boostDuration = 0.5f;
        settings_.fallVelocity = 15.0f;
        settings_.driftAcceleration = 6.0f;
        settings_.driftVelocity = 3.0f;
    }

    void DefaultCharacterActor::create()
    {
        b2BodyDef mainBodyDef;
        mainBodyDef.type = b2_dynamicBody;
        mainBodyDef.position.Set(position_.x, position_.y);
        mainBodyDef.fixedRotation = true;
        mainBody_ = gameLogic_->world()->CreateBody(&mainBodyDef);

        b2CircleShape mainShape;
        mainShape.m_radius = radius_;
        b2FixtureDef mainFixtureDef;
        mainFixtureDef.shape = &mainShape;
        mainFixtureDef.density = 1.0f;
        mainBody_->CreateFixture(&mainFixtureDef);

        b2Vec2 wheelPosition(position_.x, position_.y - 0.5 * radius_);

        b2BodyDef wheelBodyDef;
        wheelBodyDef.type = b2_dynamicBody;
        wheelBodyDef.position = wheelPosition;
        wheelBody_ = gameLogic_->world()->CreateBody(&wheelBodyDef);

        b2CircleShape wheelShape;
        wheelShape.m_radius = wheelRadius();
        b2FixtureDef wheelFixtureDef;
        wheelFixtureDef.shape = &wheelShape;
        wheelFixtureDef.density = 1.0f;
        wheelFixtureDef.friction = 5.0f;
        wheelBody_->CreateFixture(&wheelFixtureDef);

        b2CircleShape floorSensorShape;
        floorSensorShape.m_radius = wheelRadius() + 0.05f;
        b2FixtureDef floorSensorFixtureDef;
        floorSensorFixtureDef.shape = &floorSensorShape;
        floorSensorFixtureDef.isSensor = true;
        floorSensorFixture_ = wheelBody_->CreateFixture(&floorSensorFixtureDef);
        setUserData(floorSensorFixture_, this);

        b2RevoluteJointDef wheelJointDef;
        wheelJointDef.Initialize(mainBody_, wheelBody_, wheelPosition);
        wheelJointDef.maxMotorTorque = 5.0f;
        wheelJoint_ = static_cast<b2RevoluteJoint *>(gameLogic_->world()->CreateJoint(&wheelJointDef));

        state_ = createCharacterStandState(this);
        state_->enter();
    }

    void DefaultCharacterActor::destroy()
    {
        state_->leave();
        state_.reset();

        gameLogic_->world()->DestroyJoint(wheelJoint_);
        wheelJoint_ = 0;

        gameLogic_->world()->DestroyBody(wheelBody_);
        wheelBody_ = 0;
        floorSensorFixture_ = 0;

        gameLogic_->world()->DestroyBody(mainBody_);
        mainBody_ = 0;
    }

    Vector2 DefaultCharacterActor::position() const
    {
        assert(mainBody_);
        b2Vec2 position = mainBody_->GetPosition();
        return Vector2(position.x, position.y);
    }

    void DefaultCharacterActor::update(float dt)
    {
        updateSensors();
        if (updateHandler_) {
            updateHandler_->update(dt);
        }
        updateState();
    }

    void DefaultCharacterActor::addContact(b2Contact *contact)
    {
        b2Fixture *fixtureA = contact->GetFixtureA();
        b2Fixture *fixtureB = contact->GetFixtureB();
        if (fixtureA == floorSensorFixture_ || fixtureB == floorSensorFixture_)
        {
            ++floorContactCount_;
        }
    }

    void DefaultCharacterActor::removeContact(b2Contact *contact)
    {
        b2Fixture *fixtureA = contact->GetFixtureA();
        b2Fixture *fixtureB = contact->GetFixtureB();
        if (fixtureA == floorSensorFixture_ || fixtureB == floorSensorFixture_)
        {
            --floorContactCount_;
        }
    }

    CharacterActor *DefaultCharacterActor::asCharacterActor()
    {
        return this;
    }

    CharacterActor const *DefaultCharacterActor::asCharacterActor() const
    {
        return this;
    }

    CharacterSettings const *DefaultCharacterActor::settings() const
    {
        return &settings_;
    }

    CharacterSensors const *DefaultCharacterActor::sensors() const
    {
        return &sensors_;
    }

    CharacterControls const *DefaultCharacterActor::controls() const
    {
        return &controls_;
    }

    void DefaultCharacterActor::controls(CharacterControls const *controls)
    {
        assert(controls);
        controls_ = *controls;
    }

    Vector2 DefaultCharacterActor::velocity() const
    {
        b2Vec2 v = mainBody_->GetLinearVelocity();
        return Vector2(v.x, v.y);
    }

    void DefaultCharacterActor::velocity(Vector2 velocity)
    {
        mainBody_->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
        wheelBody_->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
    }

    void DefaultCharacterActor::wheelMotorEnabled(bool enabled)
    {
        wheelJoint_->EnableMotor(enabled);
    }

    void DefaultCharacterActor::wheelMotorVelocity(float velocity)
    {
        wheelJoint_->SetMotorSpeed(-velocity / wheelRadius());
    }

    void DefaultCharacterActor::wheelVelocity(float velocity)
    {
        wheelBody_->SetAngularVelocity(-velocity / wheelRadius());
    }

    void DefaultCharacterActor::updateHandler(UpdateHandler *handler)
    {
        updateHandler_ = handler;
    }

    float DefaultCharacterActor::jumpTime() const
    {
        return jumpTime_;
    }

    void DefaultCharacterActor::jumpTime(float time)
    {
        jumpTime_ = time;
    }

    bool DefaultCharacterActor::boost() const
    {
        return boost_;
    }

    void DefaultCharacterActor::boost(bool boost)
    {
        boost_ = boost;
    }

    std::auto_ptr<Actor>
        createCharacterActor(GameLogic *logic, Vector2 position, float radius)
    {
        return std::auto_ptr<Actor>(new DefaultCharacterActor(logic, position,
                                                              radius));
    }
}
