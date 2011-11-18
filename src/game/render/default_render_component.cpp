#include "default_render_component.hpp"

#include "actor.hpp"
#include "context.hpp"
#include "default_image.hpp"
#include "default_texture.hpp"
#include "game.hpp"
#include "image.hpp"
#include "image_texture_source.hpp"
#include "math.hpp"
#include "physics_component.hpp"
#include "render_component.hpp"
#include "render_service.hpp"
#include "scene.hpp"
#include "sprite.hpp"
#include "texture.hpp"
#include "texture_source.hpp"
#include "xml.hpp"

#include <boost/bind.hpp>

namespace mortified {
    class DefaultRenderComponent : public virtual RenderComponent {
    public:
        explicit DefaultRenderComponent(Actor *actor) :
            actor_(actor),
            renderService_(actor->getGame()->getRenderService())
        { }

        void load(rapidxml::xml_node<> *node, Matrix3 parentTransform)
        {
            loadSprites(node, parentTransform);
        }
        
        void save(rapidxml::xml_node<> *parentNode, Matrix3 parentTransform)
        {
            rapidxml::xml_node<> *node = saveGroup(parentNode, "render-component");
            saveSprites(node, parentTransform);
        }
        
        void draw()
        { }

    private:
        Actor *actor_;
        RenderService *renderService_;

        void loadSprites(rapidxml::xml_node<> *node, Matrix3 parentTransform)
        {
            for (rapidxml::xml_node<> *childNode = node->first_node();
                 childNode; childNode = childNode->next_sibling())
            {
                if (childNode->type() == rapidxml::node_element) {
                    if (std::strcmp(childNode->name(), "sprite") == 0) {
                        loadSprite(childNode, parentTransform);
                    }
                }
            }
        }

        void loadSprite(rapidxml::xml_node<> *node, Matrix3 parentTransform)
        {
            const char *imageRef = 0;
            Vector2 alignment;
            Vector2 position;
            float angle = 0.0f;
            Vector2 scale(1.0f);
            const char *bodyRef = 0;
            PhysicsComponent *physicsComponent = actor_->getPhysicsComponent();
            for (rapidxml::xml_node<> *childNode = node->first_node();
                 childNode; childNode = childNode->next_sibling())
            {
                if (childNode->type() == rapidxml::node_element) {
                    if (std::strcmp(childNode->name(), "image-ref") == 0) {
                        imageRef = childNode->value();
                    }
                    if (std::strcmp(childNode->name(), "alignment") == 0) {
                        alignment = loadVector2(childNode);
                    }
                    if (std::strcmp(childNode->name(), "position") == 0) {
                        position = loadVector2(childNode);
                    }
                    if (std::strcmp(childNode->name(), "angle") == 0) {
                        angle = loadFloat(childNode);
                    }
                    if (std::strcmp(childNode->name(), "scale") == 0) {
                        scale = loadVector2(childNode);
                    }
                    if (std::strcmp(childNode->name(), "body-ref") == 0) {
                        bodyRef = childNode->value();
                    }
                }
            }
            if (imageRef) {
                position = parentTransform * position;
                angle += parentTransform.rotation();
                std::string file;
                file += "../../../data/images/";
                file += imageRef;
                file += ".png";
                boost::intrusive_ptr<Image> image = loadImageFromFile(file.c_str());
                image->flipVertical();
                Scene::SpriteIterator sprite = renderService_->getScene()->createSprite();
                sprite->setImage(image);
                sprite->setAlignment(alignment);
                sprite->setPosition(position);
                sprite->setAngle(angle);
                sprite->setScale(scale);

                if (bodyRef && physicsComponent) {
                    b2Body *body = physicsComponent->findBody(bodyRef);
                    if (body) {
                        attachSpriteToBody(&*sprite, body);
                    }
                }
            }
        }

        void saveSprites(rapidxml::xml_node<> *parent, Matrix3 parentTransform)
        { }

        void attachSpriteToBody(Sprite *sprite, b2Body *body)
        {
            Vector2 position = sprite->getPosition();
            b2Vec2 localPosition = b2MulT(body->GetTransform(),
                                          b2Vec2(position.x,
                                                 position.y));
            float localAngle = sprite->getAngle() - body->GetAngle();
            RenderService::UpdateHandler handler =
                boost::bind(&DefaultRenderComponent::updateSpriteFromBody,
                            this, sprite, body, localPosition, localAngle, _1);
            renderService_->addUpdateHandler(handler);
        }

        void updateSpriteFromBody(Sprite *sprite, b2Body *body,
                                  b2Vec2 localPosition, float localAngle,
                                  float dt)
        {
            b2Vec2 position = b2Mul(body->GetTransform(), localPosition);
            sprite->setPosition(Vector2(position.x, position.y));
            sprite->setAngle(body->GetAngle() + localAngle);
        }
    };

    std::auto_ptr<RenderComponent> createRenderComponent(Actor *actor)
    {
        return std::auto_ptr<RenderComponent>(new DefaultRenderComponent(actor));
    }
}
