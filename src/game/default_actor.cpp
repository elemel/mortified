#include "default_actor.hpp"

#include "actor.hpp"
#include "component.hpp"
#include "control_component.hpp"
#include "default_control_component.hpp"
#include "default_physics_component.hpp"
#include "default_property_component.hpp"
#include "default_render_component.hpp"
#include "physics_component.hpp"
#include "property_component.hpp"
#include "render_component.hpp"
#include "xml.hpp"

#include <cstring>
#include <string>

namespace mortified {
    class DefaultActor : public virtual Actor {
    public:
        explicit DefaultActor(Game *game) :
            game_(game)
        { }

        char const *getName() const
        {
            return name_.empty() ? 0 : name_.c_str();
        }
        
        Game *getGame()
        {
            return game_;
        }

        Game const *getGame() const
        {
            return game_;
        }

        void load(rapidxml::xml_node<> *node, Matrix3 parentTransform)
        {
            rapidxml::xml_node<> *propertyNode = 0;
            rapidxml::xml_node<> *controlNode = 0;
            rapidxml::xml_node<> *physicsNode = 0;
            rapidxml::xml_node<> *renderNode = 0;
            for (rapidxml::xml_node<> *childNode = node->first_node();
                 childNode; childNode = childNode->next_sibling())
            {
                if (childNode->type() == rapidxml::node_element) {
                    if (std::strcmp(childNode->name(), "name") == 0) {
                        name_ = childNode->value();
                    }
                    if (std::strcmp(childNode->name(), "property-component") == 0) {
                        propertyNode = childNode;
                    }
                    if (std::strcmp(childNode->name(), "control-component") == 0) {
                        controlNode = childNode;
                    }
                    if (std::strcmp(childNode->name(), "physics-component") == 0) {
                        physicsNode = childNode;
                    }
                    if (std::strcmp(childNode->name(), "render-component") == 0) {
                        renderNode = childNode;
                    }
                }
            }
            if (propertyNode) {
                propertyComponent_ = createPropertyComponent(this);
                propertyComponent_->load(propertyNode, parentTransform);
            }
            if (physicsNode) {
                physicsComponent_ = createPhysicsComponent(this);
                physicsComponent_->load(physicsNode, parentTransform);
            }
            if (controlNode) {
                controlComponent_ = createControlComponent(this);
                controlComponent_->load(controlNode, parentTransform);
            }
            if (renderNode) {
                renderComponent_ = createRenderComponent(this);
                renderComponent_->load(renderNode, parentTransform);
            }
        }

        void save(rapidxml::xml_node<> *parentNode, Matrix3 parentTransform)
        {
            rapidxml::xml_node<> *node = saveGroup(parentNode, "actor");
            if (propertyComponent_.get()) {
                propertyComponent_->save(node, parentTransform);
            }
            if (controlComponent_.get()) {
                controlComponent_->save(node, parentTransform);
            }
            if (physicsComponent_.get()) {
                physicsComponent_->save(node, parentTransform);
            }
            if (renderComponent_.get()) {
                renderComponent_->save(node, parentTransform);
            }
        }

        PropertyComponent *getPropertyComponent()
        {
            return propertyComponent_.get();
        }
        
        PropertyComponent const *getPropertyComponent() const
        {
            return propertyComponent_.get();
        }

        ControlComponent *getControlComponent()
        {
            return controlComponent_.get();
        }
        
        ControlComponent const *getControlComponent() const
        {
            return controlComponent_.get();
        }
        
        PhysicsComponent *getPhysicsComponent()
        {
            return physicsComponent_.get();
        }
        
        PhysicsComponent const *getPhysicsComponent() const
        {
            return physicsComponent_.get();
        }
        
        RenderComponent *getRenderComponent()
        {
            return renderComponent_.get();
        }

        RenderComponent const *getRenderComponent() const
        {
            return renderComponent_.get();
        }
        
    private:
        std::string name_;
        Game *game_;
        std::auto_ptr<PropertyComponent> propertyComponent_;
        std::auto_ptr<PhysicsComponent> physicsComponent_;
        std::auto_ptr<ControlComponent> controlComponent_;
        std::auto_ptr<RenderComponent> renderComponent_;
    };
    
    std::auto_ptr<Actor> createActor(Game *game)
    {
        return std::auto_ptr<Actor>(new DefaultActor(game));
    }
}
