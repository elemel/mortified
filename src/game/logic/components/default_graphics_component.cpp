#include "default_graphics_component.hpp"

#include "default_image.hpp"
#include "default_sprite.hpp"
#include "default_stream.hpp"
#include "default_texture.hpp"
#include "game.hpp"
#include "game_object.hpp"
#include "graphics_component.hpp"
#include "image.hpp"
#include "image_texture_source.hpp"
#include "math.hpp"
#include "scene.hpp"
#include "sprite.hpp"
#include "stream.hpp"
#include "texture.hpp"
#include "texture_source.hpp"
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
            Vector2 alignment;
            Vector2 position;
            float angle = 0.0f;
            Vector2 scale(1.0f);
            for (rapidxml::xml_node<> *child = node->first_node();
                 child; child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element) {
                    if (std::strcmp(child->name(), "image") == 0) {
                        imageName = child->value();
                    }
                    if (std::strcmp(child->name(), "alignment") == 0) {
                        alignment = loadVector2(child);
                    }
                    if (std::strcmp(child->name(), "position") == 0) {
                        position = loadVector2(child);
                    }
                    if (std::strcmp(child->name(), "angle") == 0) {
                        angle = loadFloat(child);
                    }
                    if (std::strcmp(child->name(), "scale") == 0) {
                        scale = loadVector2(child);
                    }
                }
            }
            if (imageName) {
                std::string file;
                file += "../../../content/images/";
                file += imageName;
                file += ".png";
                std::auto_ptr<Stream> stream = createStreamFromFile(file.c_str(), "rb");
                boost::shared_ptr<Image> image = createImage(stream.get());
                image->flipVertical();
                boost::shared_ptr<Texture> texture =
                    createTexture(boost::shared_ptr<Context>(),
                                  createImageTextureSource(image));
                boost::shared_ptr<Sprite> sprite = createSprite(texture);
                sprite->alignment(alignment);
                sprite->position(position);
                sprite->angle(angle);
                sprite->scale(scale);
                object_->game()->scene()->addObject(sprite);
            }
        }

        Vector2 loadVector2(rapidxml::xml_node<> *node)
        {
            Vector2 result;
            for (rapidxml::xml_node<> *child = node->first_node();
                 child; child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element) {
                    if (std::strcmp(child->name(), "x") == 0) {
                        result.x = loadFloat(child);
                    }
                    if (std::strcmp(child->name(), "y") == 0) {
                        result.y = loadFloat(child);
                    }
                }
            }
            return result;
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
