#include "ball_actor.hpp"

#include "actor_base.hpp"
#include "game.hpp"
#include "math.hpp"

#include <iostream>
#include <Box2D/Box2D.h>

namespace mortified {
    class BallActor : public virtual ActorBase {
    public:
        BallActor(Game *game, Vector2 position, float radius);

        void create();
        void destroy();

    private:
        Vector2 position_;
        float radius_;
        b2Body *body_;
    };

    BallActor::BallActor(Game *game, Vector2 position, float radius) :
        ActorBase(game),
        position_(position),
        radius_(radius),
        body_(0)
    { }

    void BallActor::create()
    {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(position_.x, position_.y);
        body_ = game_->world()->CreateBody(&bodyDef);

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
        game_->world()->DestroyBody(body_);
        body_ = 0;
    }

    std::auto_ptr<Actor>
        createBallActor(Game *game, Vector2 position, float radius)
    {
        return std::auto_ptr<Actor>(new BallActor(game, position, radius));
    }
}
