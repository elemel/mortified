#include "default_game_object.hpp"

#include "component.hpp"
#include "control_component.hpp"
#include "default_control_component.hpp"
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
        explicit DefaultGameObject(Game *game) :
            game_(game)
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
            rapidxml::xml_node<> *controlNode = 0;
            rapidxml::xml_node<> *physicsNode = 0;
            rapidxml::xml_node<> *graphicsNode = 0;
            for (rapidxml::xml_node<> *child = node->first_node();
                 child; child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element) {
                    if (std::strcmp(child->name(), "control-component") == 0) {
                        controlNode = child;
                    }
                    if (std::strcmp(child->name(), "physics-component") == 0) {
                        physicsNode = child;
                    }
                    if (std::strcmp(child->name(), "graphics-component") == 0) {
                        graphicsNode = child;
                    }
                }
            }
            if (physicsNode) {
                physicsComponent_ = createPhysicsComponent(this);
                physicsComponent_->load(physicsNode);
            }
            if (controlNode) {
                controlComponent_ = createControlComponent(this);
                controlComponent_->load(controlNode);
            }
            if (graphicsNode) {
                graphicsComponent_ = createGraphicsComponent(this);
                graphicsComponent_->load(graphicsNode);
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

        ControlComponent *controlComponent()
        {
            return controlComponent_.get();
        }
        
        ControlComponent const *controlComponent() const
        {
            return controlComponent_.get();
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
        std::auto_ptr<PhysicsComponent> physicsComponent_;
        std::auto_ptr<ControlComponent> controlComponent_;
        std::auto_ptr<GraphicsComponent> graphicsComponent_;
    };
    
    boost::shared_ptr<GameObject>
    createGameObject(Game *game)
    {
        return boost::shared_ptr<GameObject>(new DefaultGameObject(game));
    }
}
