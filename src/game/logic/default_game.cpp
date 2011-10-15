#include "default_game.hpp"

#include "actor.hpp"
#include "game.hpp"
#include "physics_contact_listener.hpp"

#include <cassert>
#include <iostream>
#include <vector>
#include <Box2D/Box2D.h>

namespace mortified {
    class DefaultGame : public virtual Game {
    public:
        DefaultGame() :
            time_(0.0f),
            hero_(0)
        {
            b2Vec2 gravity(0.0f, -15.0f);
            world_.reset(new b2World(gravity, true));
            contactListener_.reset(new PhysicsContactListener);
            world_->SetContactListener(contactListener_.get());
        }

        ~DefaultGame()
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

        ObjectRange objects()
        {
            return ObjectRange(objects_.begin(), objects_.end());
        }

        ConstObjectRange objects() const
        {
            return ConstObjectRange(objects_.begin(), objects_.end());
        }
        
        ObjectIterator addObject(ObjectPtr object)
        {
            return objects_.insert(objects_.end(), object);
        }

        void removeObject(ObjectIterator object)
        {
            objects_.erase(object);
        }

    private:
        float time_;
        std::auto_ptr<b2World> world_;
        std::auto_ptr<PhysicsContactListener> contactListener_;
        std::vector<Actor *> actors_;
        CharacterActor *hero_;
        ObjectList objects_;
    };

    std::auto_ptr<Game> createGame()
    {
        return std::auto_ptr<Game>(new DefaultGame);
    }
}
