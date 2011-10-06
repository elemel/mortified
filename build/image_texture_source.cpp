#include "image_texture_source.hpp"

#include "image.hpp"

#include <boost/shared_ptr.hpp>

namespace mortified {
    class ImageTextureSource : public virtual TextureSource {
    public:
        explicit ImageTextureSource(boost::shared_ptr<Image> image) :
            image_(image)
        { }

        bool exists() const
        {
            return true;
        }

        void create()
        { }

        void destroy()
        { }

        int width() const
        {
            return image_->width();
        }

        int height() const
        {
            return image_->height();
        }

        void const *pixels() const
        {
            return image_->pixels();
        }

    private:
        boost::shared_ptr<Image> image_;
    };

    boost::shared_ptr<TextureSource>
        createImageTextureSource(boost::shared_ptr<Image> image)
    {
        return boost::shared_ptr<TextureSource>(new ImageTextureSource(image));
    }
}
