#include "image_texture_source.hpp"

#include "image.hpp"
#include "ref_counted_base.hpp"

#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class ImageTextureSource :
        public virtual TextureSource,
        private virtual RefCountedBase
    {
    public:
        explicit ImageTextureSource(boost::intrusive_ptr<Image> image) :
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

        int getWidth() const
        {
            return image_->getWidth();
        }

        int getHeight() const
        {
            return image_->getHeight();
        }

        void const *getPixels() const
        {
            return image_->getPixels();
        }

    private:
        boost::intrusive_ptr<Image> image_;
    };

    boost::intrusive_ptr<TextureSource>
    createImageTextureSource(boost::intrusive_ptr<Image> image)
    {
        return boost::intrusive_ptr<TextureSource>(new ImageTextureSource(image));
    }
}
