#include "default_render_service.hpp"

#include "color.hpp"
#include "context.hpp"
#include "default_scene.hpp"
#include "default_sparse_image.hpp"
#include "math.hpp"
#include "render_service.hpp"
#include "scene.hpp"
#include "sparse_image.hpp"

#include <SDL/SDL_opengl.h>

namespace mortified {
    class DefaultRenderService : public virtual RenderService {
    public:
        explicit DefaultRenderService(boost::intrusive_ptr<Context> context) :
            scene_(createScene(context)),
            sparseImage_(createSparseImage()),
            sparseImageAngle_(0.5),
            sparseImageScale_(0.1)
        {
            Color4 color(0, 127, 255, 255);
            sparseImage_->setPixel(0, 0, color);
            sparseImage_->setPixel(0, 1, color);
            sparseImage_->setPixel(0, 2, color);
            sparseImage_->setPixel(0, 3, color);
            sparseImage_->setPixel(0, 4, color);
            sparseImage_->setPixel(1, 3, color);
            sparseImage_->setPixel(2, 2, color);
            sparseImage_->setPixel(3, 3, color);
            sparseImage_->setPixel(4, 0, color);
            sparseImage_->setPixel(4, 1, color);
            sparseImage_->setPixel(4, 2, color);
            sparseImage_->setPixel(4, 3, color);
            sparseImage_->setPixel(4, 4, color);
            
            sparseImage_->setPixel(6, 1, color);
            sparseImage_->setPixel(6, 2, color);
            sparseImage_->setPixel(6, 3, color);
            sparseImage_->setPixel(7, 0, color);
            sparseImage_->setPixel(7, 4, color);
            sparseImage_->setPixel(8, 0, color);
            sparseImage_->setPixel(8, 4, color);
            sparseImage_->setPixel(9, 1, color);
            sparseImage_->setPixel(9, 2, color);
            sparseImage_->setPixel(9, 3, color);
            
            sparseImage_->setPixel(11, 0, color);
            sparseImage_->setPixel(11, 1, color);
            sparseImage_->setPixel(11, 2, color);
            sparseImage_->setPixel(11, 3, color);
            sparseImage_->setPixel(11, 4, color);
            sparseImage_->setPixel(12, 2, color);
            sparseImage_->setPixel(12, 4, color);
            sparseImage_->setPixel(13, 2, color);
            sparseImage_->setPixel(13, 4, color);
            sparseImage_->setPixel(14, 0, color);
            sparseImage_->setPixel(14, 1, color);
            sparseImage_->setPixel(14, 3, color);
            
            sparseImage_->setPixel(16, 3, color);
            sparseImage_->setPixel(16, 4, color);
            sparseImage_->setPixel(17, 4, color);
            sparseImage_->setPixel(18, 0, color);
            sparseImage_->setPixel(18, 1, color);
            sparseImage_->setPixel(18, 2, color);
            sparseImage_->setPixel(18, 3, color);
            sparseImage_->setPixel(18, 4, color);
            sparseImage_->setPixel(19, 4, color);
            sparseImage_->setPixel(20, 3, color);
            sparseImage_->setPixel(20, 4, color);
        }

        void load(rapidxml::xml_node<> *node)
        { }
        
        void save(rapidxml::xml_node<> *parent)
        { }

        void update(float dt)
        {
            for (UpdateHandlerIterator i = handlers_.begin();
                 i != handlers_.end(); ++i)
            {
                (*i)(dt);
            }
        }

        UpdateHandlerIterator addUpdateHandler(UpdateHandler handler)
        {
            return handlers_.insert(handlers_.end(), handler);
        }

        void removeUpdateHandler(UpdateHandlerIterator handler)
        {
            handlers_.erase(handler);
        }

        Scene *getScene()
        {
            return scene_.get();
        }

        Scene const *getScene() const
        {
            return scene_.get();
        }

        void draw()
        {
            scene_->draw();
            drawSparseImage();
        }

    private:
        std::auto_ptr<Scene> scene_;
        UpdateHandlerList handlers_;
        
        std::auto_ptr<SparseImage> sparseImage_;
        Vector2 sparseImagePosition_;
        float sparseImageAngle_;
        float sparseImageScale_;

        void drawSparseImage()
        {
            glPushMatrix();
            glTranslatef(sparseImagePosition_.x, sparseImagePosition_.y, 0.0f);
            glRotatef(sparseImageAngle_ * 180.0f / M_PI, 0.0f, 0.0f, 1.0f);
            glScalef(sparseImageScale_, sparseImageScale_, 1.0f);
            sparseImage_->draw();
            glPopMatrix();
        }
    };

    std::auto_ptr<RenderService>
    createRenderService(boost::intrusive_ptr<Context> context)
    {
        return std::auto_ptr<RenderService>(new DefaultRenderService(context));
    }
}
