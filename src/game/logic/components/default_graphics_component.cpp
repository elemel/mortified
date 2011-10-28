#include "default_graphics_component.hpp"

#include "default_image.hpp"
#include "default_sprite.hpp"
#include "default_stream.hpp"
#include "default_texture.hpp"
#include "game.hpp"
#include "game_object.hpp"
#include "graphics_component.hpp"
#include "graphics_service.hpp"
#include "image.hpp"
#include "image_texture_source.hpp"
#include "math.hpp"
#include "physics_component.hpp"
#include "scene.hpp"
#include "sprite.hpp"
#include "stream.hpp"
#include "texture.hpp"
#include "texture_source.hpp"
#include "xml.hpp"

#include <boost/bind.hpp>

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
            const char *imageRef = 0;
            Vector2 alignment;
            Vector2 position;
            float angle = 0.0f;
            Vector2 scale(1.0f);
            const char *bodyRef = 0;
            PhysicsComponent *physicsComponent = object_->physicsComponent();
            for (rapidxml::xml_node<> *child = node->first_node();
                 child; child = child->next_sibling())
            {
                if (child->type() == rapidxml::node_element) {
                    if (std::strcmp(child->name(), "image-ref") == 0) {
                        imageRef = child->value();
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
                    if (std::strcmp(child->name(), "body-ref") == 0) {
                        bodyRef = child->value();
                    }
                }
            }
            if (imageRef) {
                std::string file;
                file += "../../../content/images/";
                file += imageRef;
                file += ".png";
                std::auto_ptr<Stream> stream =
                    createStreamFromFile(file.c_str(), "rb");
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
                object_->game()->graphicsService()->scene()->addObject(sprite);

                if (bodyRef && physicsComponent) {
                    b2Body *body = physicsComponent->findBody(bodyRef);
                    if (body) {
                        attachSpriteToBody(sprite.get(), body);
                    }
                }
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

        void attachSpriteToBody(Sprite *sprite, b2Body *body)
        {
            Vector2 position = sprite->position();
            b2Vec2 localPosition = b2MulT(body->GetTransform(),
                                          b2Vec2(position.x,
                                                 position.y));
            float localAngle = sprite->angle() - body->GetAngle();
            GraphicsService::UpdateHandler handler =
            boost::bind(&DefaultGraphicsComponent::updateSpriteFromBody,
                        this, sprite, body, localPosition, localAngle, _1);
            object_->game()->graphicsService()->addUpdateHandler(handler);
        }

        void updateSpriteFromBody(Sprite *sprite, b2Body *body,
                                  b2Vec2 localPosition, float localAngle,
                                  float dt)
        {
            b2Vec2 position = b2Mul(body->GetTransform(), localPosition);
            sprite->position(Vector2(position.x, position.y));
            sprite->angle(body->GetAngle() + localAngle);
        }
    };

    std::auto_ptr<GraphicsComponent>
    createGraphicsComponent(GameObject *object)
    {
        return std::auto_ptr<GraphicsComponent>(new DefaultGraphicsComponent(object));
    }
}
