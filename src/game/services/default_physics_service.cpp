#include "default_physics_service.hpp"

#include "physics_contact_listener.hpp"
#include "physics_service.hpp"

namespace mortified {
    class DefaultPhysicsService : public virtual PhysicsService {
    public:
        DefaultPhysicsService()
        {
            // TODO: Load physics config from XML.
            b2Vec2 gravity(0.0f, -15.0f);
            world_.reset(new b2World(gravity));
            contactListener_ = createPhysicsContactListener();
            world_->SetContactListener(contactListener_.get());
        }        

        void load(rapidxml::xml_node<> *node)
        { }
        
        void save(rapidxml::xml_node<> *parent)
        { }

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
