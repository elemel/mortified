#include "default_graphics_component.hpp"

#include "actor.hpp"
#include "context.hpp"
#include "default_image.hpp"
#include "default_sprite.hpp"
#include "default_texture.hpp"
#include "game.hpp"
#include "graphics_component.hpp"
#include "graphics_service.hpp"
#include "image.hpp"
#include "image_texture_source.hpp"
#include "math.hpp"
#include "physics_component.hpp"
#include "scene.hpp"
#include "sprite.hpp"
#include "texture.hpp"
#include "texture_source.hpp"
#include "xml.hpp"

#include <boost/bind.hpp>

namespace mortified {
    class DefaultGraphicsComponent : public virtual GraphicsComponent {
    public:
        explicit DefaultGraphicsComponent(Actor *actor) :
            actor_(actor),
            graphicsService_(actor->game()->graphicsService())
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
        Actor *actor_;
        GraphicsService *graphicsService_;

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
            PhysicsComponent *physicsComponent = actor_->physicsComponent();
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
                boost::intrusive_ptr<Image> image = loadImageFromFile(file.c_str());
                image->flipVertical();
                boost::intrusive_ptr<Texture> texture =
                    createTexture(boost::intrusive_ptr<Context>(),
                                  createImageTextureSource(image));
                boost::intrusive_ptr<Sprite> sprite = createSprite(texture);
                sprite->alignment(alignment);
                sprite->position(position);
                sprite->angle(angle);
                sprite->scale(scale);
                graphicsService_->scene()->addObject(sprite);

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
            graphicsService_->addUpdateHandler(handler);
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

    std::auto_ptr<GraphicsComponent> createGraphicsComponent(Actor *actor)
    {
        return std::auto_ptr<GraphicsComponent>(new DefaultGraphicsComponent(actor));
    }
}
