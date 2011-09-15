#include "default_game_logic.hpp"

#include "actor.hpp"
#include "game_logic.hpp"
#include "physics_contact_listener.hpp"

#include <cassert>
#include <iostream>
#include <vector>
#include <Box2D/Box2D.h>

namespace mortified {
    class DefaultGameLogic : public GameLogic {
    public:
        DefaultGameLogic() :
            time_(0.0f),
            hero_(0)
        {
            b2Vec2 gravity(0.0f, -15.0f);
            world_.reset(new b2World(gravity, true));
            contactListener_.reset(new PhysicsContactListener);
            world_->SetContactListener(contactListener_.get());
        }

        ~DefaultGameLogic()
        {
            while (!actors_.empty()) {
                assert(actors_.back());
                removeActor(actors_.back());
            }
        }

        float time() const
        {
            return time_;
        }

        b2World *world()
        {
            return world_.get();
        }

        void update(float dt)
        {
            time_ += dt;

            for (std::size_t i = 0; i < actors_.size(); ++i) {
                if (actors_[i]) {
                    actors_[i]->update(dt);
                }
            }

            world_->Step(dt, 10, 10);

            std::size_t j = 0;
            for (std::size_t i = 0; i < actors_.size(); ++i) {
                if (actors_[i]) {
                    actors_[j++] = actors_[i];
                }
            }
            actors_.resize(j);
        }

        void addActor(std::auto_ptr<Actor> actor)
        {
            assert(actor.get());
            actors_.push_back(actor.release());
            actors_.back()->create();
        }

        std::auto_ptr<Actor> removeActor(Actor *actor)
        {
            assert(actor);
            for (std::size_t i = actors_.size(); i > 0; --i) {
                if (actors_[i - 1] == actor) {
                    actors_[i - 1] = 0;
                    while (!actors_.empty() && actors_.back() == 0) {
                        actors_.pop_back();
                    }

                    std::auto_ptr<Actor> result(actor);
                    result->destroy();
                    return result;
                }
            }
            return std::auto_ptr<Actor>();
        }

        CharacterActor *hero()
        {
            return hero_;
        }

        void hero(CharacterActor *hero)
        {
            hero_ = hero;
        }

    private:
        float time_;
        std::auto_ptr<b2World> world_;
        std::auto_ptr<PhysicsContactListener> contactListener_;
        std::vector<Actor *> actors_;
        CharacterActor *hero_;
    };

    std::auto_ptr<GameLogic> createGameLogic()
    {
        return std::auto_ptr<GameLogic>(new DefaultGameLogic);
    }
}
