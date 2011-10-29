#include "default_game_object.hpp"

#include "component.hpp"
#include "default_graphics_component.hpp"
#include "default_physics_component.hpp"
#include "game_object.hpp"
#include "graphics_component.hpp"
#include "physics_component.hpp"
#include "xml.hpp"

#include <cstring>

namespace mortified {
    class DefaultGameObject : public virtual GameObject {
    public:
        DefaultGameObject(Game *game, Matrix3 transform) :
            game_(game),
            transform_(transform)
        { }

        Game *game()
        {
            return game_;
        }

        Game const *game() const
        {
            return game_;
        }

        void load(rapidxml::xml_node<> *node)
        {
            for (rapidxml::xml_node<> *child = node->first_node();
                 child; child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element) {
                    if (std::strcmp(child->name(), "physics-component") == 0) {
                        physicsComponent_ = createPhysicsComponent(this);
                        physicsComponent_->load(child);
                    }
                    if (std::strcmp(child->name(), "graphics-component") == 0) {
                        graphicsComponent_ = createGraphicsComponent(this);
                        graphicsComponent_->load(child);
                    }
                }
            }
        }

        void save(rapidxml::xml_node<> *parent)
        {
            rapidxml::xml_node<> *node = saveGroup(parent, "object");
            if (physicsComponent_.get()) {
                physicsComponent_->save(node);
            }
            if (graphicsComponent_.get()) {
                graphicsComponent_->save(node);
            }
        }

        PhysicsComponent *physicsComponent()
        {
            return physicsComponent_.get();
        }
        
        PhysicsComponent const *physicsComponent() const
        {
            return physicsComponent_.get();
        }
        
        GraphicsComponent *graphicsComponent()
        {
            return graphicsComponent_.get();
        }

        GraphicsComponent const *graphicsComponent() const
        {
            return graphicsComponent_.get();
        }
        
    private:
        Game *game_;
        Matrix3 transform_;
        std::auto_ptr<PhysicsComponent> physicsComponent_;
        std::auto_ptr<GraphicsComponent> graphicsComponent_;
    };
    
    boost::shared_ptr<GameObject>
    createGameObject(Game *game, Matrix3 transform)
    {
        return boost::shared_ptr<GameObject>(new DefaultGameObject(game, transform));
    }
}
