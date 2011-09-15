#include "ball_actor.hpp"

#include "actor_base.hpp"
#include "game_logic.hpp"
#include "math.hpp"

#include <iostream>
#include <Box2D/Box2D.h>

namespace mortified {
    class BallActor : public virtual ActorBase {
    public:
        BallActor(GameLogic *logic, Vector2 position, float radius);

        void create();
        void destroy();

    private:
        Vector2 position_;
        float radius_;
        b2Body *body_;
    };

    BallActor::BallActor(GameLogic *logic, Vector2 position, float radius) :
        ActorBase(logic),
        position_(position),
        radius_(radius),
        body_(0)
    { }

    void BallActor::create()
    {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(position_.x, position_.y);
        body_ = gameLogic_->world()->CreateBody(&bodyDef);

        b2CircleShape circleShape;
        circleShape.m_radius = radius_;
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &circleShape;
        fixtureDef.density = 1.0f;
        fixtureDef.restitution = 0.8f;
        body_->CreateFixture(&fixtureDef);
    }

    void BallActor::destroy()
    {
        gameLogic_->world()->DestroyBody(body_);
        body_ = 0;
    }

    std::auto_ptr<Actor>
        createBallActor(GameLogic *logic, Vector2 position, float radius)
    {
        return std::auto_ptr<Actor>(new BallActor(logic, position, radius));
    }
}
