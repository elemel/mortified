#include "default_scene.hpp"

#include "scene.hpp"
#include "sprite.hpp"
#include "sprite_controller.hpp"

#include <cassert>
#include <iostream>
#include <vector>

namespace mortified {
    class DefaultScene :
        public virtual Scene
    {
    public:
        ~DefaultScene()
        {
            removeAllSpriteControllers();
            removeAllSprites();
        }

        void addSpriteController(std::auto_ptr<SpriteController> controller)
        {
            assert(controller.get());
            spriteControllers_.push_back(0);
            spriteControllers_.back() = controller.release();
            spriteControllers_.back()->create();
        }

        std::auto_ptr<SpriteController>
            removeSpriteController(SpriteController *controller)
        {
            for (std::size_t i = spriteControllers_.size(); i > 0; --i) {
                if (spriteControllers_[i - 1] == controller) {
                    spriteControllers_[i - 1] = 0;
                    while (!spriteControllers_.empty() && spriteControllers_.back() == 0) {
                        spriteControllers_.pop_back();
                    }
                    std::auto_ptr<SpriteController> result(controller);
                    controller->destroy();
                    return result;
                }
            }
            return std::auto_ptr<SpriteController>();
        }

        void addSprite(std::auto_ptr<Sprite> sprite)
        {
            assert(sprite.get());
            sprites_.push_back(0);
            sprites_.back() = sprite.release();
        }

        std::auto_ptr<Sprite> removeSprite(Sprite *sprite)
        {
            assert(sprite);
            for (std::size_t i = sprites_.size(); i > 0; --i) {
                if (sprites_[i - 1] == sprite) {
                    sprites_[i - 1] = 0;
                    while (!sprites_.empty() && sprites_.back() == 0) {
                        sprites_.pop_back();
                    }
                    return std::auto_ptr<Sprite>(sprite);
                }
            }
            return std::auto_ptr<Sprite>();
        }

        void update()
        {
            for (std::size_t i = 0; i < spriteControllers_.size(); ++i) {
                if (spriteControllers_[i]) {
                    spriteControllers_[i]->update();
                }
            }

            std::size_t j = 0;
            for (std::size_t i = 0; i < spriteControllers_.size(); ++i) {
                if (spriteControllers_[i]) {
                    spriteControllers_[j++] = spriteControllers_[i];
                }
            }
            spriteControllers_.resize(j);
        }

        void draw()
        {
            std::size_t j = 0;
            for (std::size_t i = 0; i < sprites_.size(); ++i) {
                if (sprites_[i]) {
                    sprites_[i]->draw();
                    sprites_[j++] = sprites_[i];
                }
            }
            sprites_.resize(j);
        }

    private:
        std::vector<SpriteController *> spriteControllers_;
        std::vector<Sprite *> sprites_;

        void removeAllSprites()
        {
            while (!sprites_.empty()) {
                removeSprite(sprites_.back());
            }
        }

        void removeAllSpriteControllers()
        {
            while (!spriteControllers_.empty()) {
                removeSpriteController(spriteControllers_.back());
            }
        }
    };

    std::auto_ptr<Scene> createScene()
    {
        return std::auto_ptr<Scene>(new DefaultScene);
    }
}
