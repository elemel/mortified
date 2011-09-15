#include "platform_actor.hpp"

#include "actor.hpp"
#include "actor_base.hpp"
#include "game_logic.hpp"
#include "math.hpp"

#include <iostream>
#include <Box2D/Box2D.h>

namespace mortified {
    class PlatformActor : public virtual Actor, private virtual ActorBase {
    public:
        PlatformActor(GameLogic *logic, Vector2 position, Vector2 size,
                      float angle);

        void create();
        void destroy();

    private:
        Vector2 position_;
        Vector2 size_;
        float angle_;
        b2Body *body_;
    };

    PlatformActor::PlatformActor(GameLogic *logic, Vector2 position,
                                 Vector2 size, float angle) :
        ActorBase(logic),
        position_(position),
        size_(size),
        angle_(angle),
        body_(0)
    { }

    void PlatformActor::create()
    {
        b2BodyDef bodyDef;
        bodyDef.position.Set(position_.x, position_.y);
        bodyDef.angle = angle_;
        body_ = gameLogic_->world()->CreateBody(&bodyDef);

        b2PolygonShape polygonShape;
        polygonShape.SetAsBox(size_.x, size_.y);
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &polygonShape;
        fixtureDef.density = 1.0f;
        body_->CreateFixture(&fixtureDef);
    }

    void PlatformActor::destroy()
    {
        gameLogic_->world()->DestroyBody(body_);
        body_ = 0;
    }

    std::auto_ptr<Actor>
        createPlatformActor(GameLogic *logic, Vector2 position, Vector2 size,
                            float angle)
    {
        return std::auto_ptr<Actor>(new PlatformActor(logic, position, size,
                                                      angle));
    }
}
