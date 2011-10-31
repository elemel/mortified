#include "default_physics_service.hpp"

#include "physics_service.hpp"

namespace mortified {
    namespace {
        class DefaultContactListener : public b2ContactListener {
        public:
            void BeginContact(b2Contact *contact)
            { }
            
            void EndContact(b2Contact* contact)
            { }
        };
    }

    class DefaultPhysicsService : public virtual PhysicsService {
    public:
        DefaultPhysicsService()
        {
            b2Vec2 gravity(0.0f, -15.0f);
            world_.reset(new b2World(gravity));
            contactListener_.reset(new DefaultContactListener);
            world_->SetContactListener(contactListener_.get());
        }        
        
        void update(float dt)
        {
            world_->Step(dt, 10, 10);
        }

        b2World *world()
        {
            return world_.get();
        }

        b2World const *world() const
        {
            return world_.get();
        }

    private:
        std::auto_ptr<b2World> world_;
        std::auto_ptr<b2ContactListener> contactListener_;
    };
    
    std::auto_ptr<PhysicsService> createPhysicsService()
    {
        return std::auto_ptr<PhysicsService>(new DefaultPhysicsService);
    }
}
