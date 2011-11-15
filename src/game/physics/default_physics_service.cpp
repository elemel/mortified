#include "default_physics_service.hpp"

#include "physics_contact_listener.hpp"
#include "physics_service.hpp"
#include "xml.hpp"

namespace mortified {
    class DefaultPhysicsService : public virtual PhysicsService {
    public:
        DefaultPhysicsService() :
            velocityIterations_(10),
            positionIterations_(10)
        {
            b2Vec2 gravity(0.0f, -10.0f);
            world_.reset(new b2World(gravity));
            contactListener_ = createPhysicsContactListener();
            world_->SetContactListener(contactListener_.get());
        }        

        void load(rapidxml::xml_node<> *node)
        {
            for (rapidxml::xml_node<> *child = node->first_node(); child;
                 child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element) {
                    if (strcmp(child->name(), "gravity") == 0) {
                        b2Vec2 gravity = loadVec2(child);
                        world_->SetGravity(gravity);
                    }
                    if (strcmp(child->name(), "velocity-iterations") == 0) {
                        velocityIterations_ = loadInt(child);
                    }
                    if (strcmp(child->name(), "position-iterations") == 0) {
                        positionIterations_ = loadInt(child);
                    }
                }
            }
        }
        
        void save(rapidxml::xml_node<> *parent)
        {
            rapidxml::xml_node<> *node = saveGroup(parent, "physics-service");
            saveVec2(node, "gravity", world_->GetGravity());
            saveInt(node, "velocity-iterations", velocityIterations_);
            saveInt(node, "position-iterations", positionIterations_);
        }

        void update(float dt)
        {
            world_->Step(dt, velocityIterations_, positionIterations_);
        }

        b2World *getWorld()
        {
            return world_.get();
        }

        b2World const *getWorld() const
        {
            return world_.get();
        }

    private:
        int velocityIterations_;
        int positionIterations_;
        std::auto_ptr<b2World> world_;
        std::auto_ptr<b2ContactListener> contactListener_;

        b2Vec2 loadVec2(rapidxml::xml_node<> *node)
        {
            b2Vec2 vec;
            vec.SetZero();
            for (rapidxml::xml_node<> *child = node->first_node();
                 child; child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element) {
                    if (std::strcmp(child->name(), "x") == 0) {
                        vec.x = loadFloat(child);
                    }
                    if (std::strcmp(child->name(), "y") == 0) {
                        vec.y = loadFloat(child);
                    }
                }
            }
            return vec;
        }

        void saveVec2(rapidxml::xml_node<> *parent, char const *name,
                      b2Vec2 vec)
        {
            rapidxml::xml_node<> *node = saveGroup(parent, name);
            saveFloat(node, "x", vec.x);
            saveFloat(node, "y", vec.y);
        }
    };
    
    std::auto_ptr<PhysicsService> createPhysicsService()
    {
        return std::auto_ptr<PhysicsService>(new DefaultPhysicsService);
    }
}
