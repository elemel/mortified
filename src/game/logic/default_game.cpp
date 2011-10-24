#include "default_game.hpp"

#include "default_graphics_service.hpp"
#include "default_physics_service.hpp"
#include "game.hpp"
#include "graphics_service.hpp"
#include "physics_service.hpp"

#include <cassert>
#include <iostream>
#include <vector>
#include <Box2D/Box2D.h>

namespace mortified {
    class DefaultGame : public virtual Game {
    public:
        DefaultGame() :
            time_(0.0f),
            physicsService_(createPhysicsService()),
            graphicsService_(createGraphicsService())
        { }

        float time() const
        {
            return time_;
        }

        PhysicsService *physicsService()
        {
            return physicsService_.get();
        }
        
        PhysicsService const *physicsService() const
        {
            return physicsService_.get();
        }

        GraphicsService *graphicsService()
        {
            return graphicsService_.get();
        }
        
        GraphicsService const *graphicsService() const
        {
            return graphicsService_.get();
        }

        void update(float dt)
        {
            time_ += dt;
            physicsService_->update(dt);
            graphicsService_->update(dt);
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
        std::auto_ptr<PhysicsService> physicsService_;
        std::auto_ptr<GraphicsService> graphicsService_;
        ObjectList objects_;
    };

    std::auto_ptr<Game> createGame()
    {
        return std::auto_ptr<Game>(new DefaultGame);
    }
}
