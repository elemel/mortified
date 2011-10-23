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
                    if (std::strcmp(child->name(), "graphics-component") == 0) {
                        ComponentPtr component = createGraphicsComponent(this);
                        component->load(child);
                        addComponent(component);
                    }
                    if (std::strcmp(child->name(), "physics-component") == 0) {
                        ComponentPtr component = createPhysicsComponent(this);
                        component->load(child);
                        addComponent(component);
                    }
                }
            }
        }

        void save(rapidxml::xml_node<> *parent)
        {
            rapidxml::xml_node<> *node = saveGroup(parent, "object");
            for (ComponentIterator i = components_.begin();
                 i != components_.end(); ++i)
            {
                (*i)->save(node);
            }
        }

        ComponentRange components()
        {
            return ComponentRange(components_.begin(), components_.end());
        }

        ConstComponentRange components() const
        {
            return ConstComponentRange(components_.begin(), components_.end());
        }
        
        ComponentIterator addComponent(ComponentPtr component)
        {
            return components_.insert(components_.end(), component);
        }

        void removeComponent(ComponentIterator component)
        {
            components_.erase(component);
        }

        void update(float dt)
        {
            for (ComponentIterator i = components_.begin();
                 i != components_.end(); ++i)
            {
                (*i)->update(dt);
            }
        }

    private:
        Game *game_;
        Matrix3 transform_;
        ComponentList components_;
    };
    
    boost::shared_ptr<GameObject>
    createGameObject(Game *game, Matrix3 transform)
    {
        return boost::shared_ptr<GameObject>(new DefaultGameObject(game, transform));
    }
}
