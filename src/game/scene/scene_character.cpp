#include "scene_character.hpp"

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
#include "scene_object_base.hpp"
#include "sprite.hpp"
#include "stream.hpp"
#include "texture.hpp"

#include <stdexcept>
#include <SDL/SDL_image.h>
#include <SDL/SDL_opengl.h>

namespace mortified {
    class SceneCharacter :
        public virtual SceneObject,
        private virtual SceneObjectBase
    {
    public:
        explicit SceneCharacter(Scene *scene, CharacterActor *actor) :
            scene_(scene),
            characterActor_(actor)
        { }

        void create()
        {
            std::auto_ptr<Stream> headImageStream =
                createStreamFromFile("../../../content/images/wizard/head.png", "rb");
            headImage_ = createImage(headImageStream.get());
            headImage_->flipVertical();
            headTexture_ = createTexture(boost::shared_ptr<Context>(), createImageTextureSource(headImage_));
            headTexture_->create();
            headSprite_ = createSprite(headTexture_);
            headSprite_->scale(0.1f);
            headSprite_->alignment(Vector2(0.5f, 0.5f));
            headSpriteIterator_ = scene_->addObject(headSprite_);
        }

        void destroy()
        {
            scene_->removeObject(headSpriteIterator_);
            headTexture_.reset();
        }

        void update(float dt)
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
        boost::shared_ptr<Sprite> headSprite_;
        Scene::ObjectIterator headSpriteIterator_;
    };

    boost::shared_ptr<SceneObject>
    createSceneCharacter(Scene *scene, CharacterActor *actor)
    {
        return boost::shared_ptr<SceneObject>(new SceneCharacter(scene, actor));
    }
}
