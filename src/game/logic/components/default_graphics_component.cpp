#include "default_graphics_component.hpp"

#include "game_object.hpp"
#include "graphics_component.hpp"
#include "xml.hpp"

namespace mortified {
    class DefaultGraphicsComponent : public virtual GraphicsComponent {
    public:
        explicit DefaultGraphicsComponent(GameObject *object) :
            object_(object)
        { }

        void load(rapidxml::xml_node<> *node)
        {
            loadSprites(node);
        }
        
        void save(rapidxml::xml_node<> *parent)
        {
            rapidxml::xml_node<> *node = saveGroup(parent, "graphics-component");
            saveSprites(node);
        }
        
        void update(float dt)
        { }
        
        void draw()
        { }

    private:
        GameObject *object_;

        void loadSprites(rapidxml::xml_node<> *node)
        {
            for (rapidxml::xml_node<> *child = node->first_node();
                 child; child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element) {
                    if (std::strcmp(child->name(), "sprite") == 0) {
                        loadSprite(child);
                    }
                }
            }
        }

        void loadSprite(rapidxml::xml_node<> *node)
        {
            const char *imageName = 0;
            for (rapidxml::xml_node<> *child = node->first_node();
                 child; child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element) {
                    if (std::strcmp(child->name(), "image") == 0) {
                        imageName = child->value();
                    }
                }
            }
        }

        void saveSprites(rapidxml::xml_node<> *parent)
        { }
    };

    boost::shared_ptr<GraphicsComponent>
    createGraphicsComponent(GameObject *object)
    {
        return boost::shared_ptr<GraphicsComponent>(new DefaultGraphicsComponent(object));
    }
}
