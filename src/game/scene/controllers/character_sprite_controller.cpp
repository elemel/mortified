#include "character_sprite_controller.hpp"

#include "character_actor.hpp"
#include "default_image.hpp"
#include "default_sprite.hpp"
#include "default_stream.hpp"
#include "default_texture.hpp"
#include "game_logic.hpp"
#include "image.hpp"
#include "image_texture_source.hpp"
#include "math.hpp"
#include "scene.hpp"
#include "sprite.hpp"
#include "sprite_controller.hpp"
#include "stream.hpp"
#include "texture.hpp"

#include <stdexcept>
#include <SDL/SDL_image.h>
#include <SDL/SDL_opengl.h>

namespace mortified {
    class CharacterSpriteController :
        public virtual SpriteController
    {
    public:
        explicit CharacterSpriteController(Scene *scene,
                                           CharacterActor *actor) :
            scene_(scene),
            characterActor_(actor),
            headSprite_(0)
        { }

        void create()
        {
            std::auto_ptr<Stream> headImageStream =
                createStreamFromFile("../../../content/images/wizard/head.png", "rb");
            headImage_ = createImage(headImageStream.get());
            headImage_->flipVertical();
            headTexture_ = createTexture(boost::shared_ptr<Context>(), createImageTextureSource(headImage_));
            headTexture_->create();
            std::auto_ptr<Sprite> sprite = createSprite(headTexture_.get());
            sprite->scale(0.1f);
            sprite->angle(-0.1f);
            sprite->alignment(Vector2(0.5f, 0.5f));
            headSprite_ = sprite.get();
            scene_->addSprite(sprite);
        }

        void destroy()
        {
            if (headSprite_) {
                scene_->removeSprite(headSprite_);
                headSprite_ = 0;
            }
            headTexture_.reset();
        }

        void update()
        {
            headSprite_->position(characterActor_->position() + Vector2(0.1f, 0.5f));
            headSprite_->angle(0.05f * std::sin(characterActor_->position().x) +
                               0.05f * std::sin(3.0f * characterActor_->gameLogic()->time()));
        }

    private:
        Scene *scene_;
        CharacterActor *characterActor_;
        boost::shared_ptr<Image> headImage_;
        boost::shared_ptr<Texture> headTexture_;
        Sprite *headSprite_;
    };

    std::auto_ptr<SpriteController>
    createCharacterSpriteController(Scene *scene, CharacterActor *actor)
    {
        return std::auto_ptr<SpriteController>(new CharacterSpriteController(scene, actor));
    }
}
