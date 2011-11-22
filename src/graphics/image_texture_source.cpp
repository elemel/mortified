#include "image_texture_source.hpp"

#include "image.hpp"

namespace mortified {
    class ImageTextureSource : public virtual TextureSource {
    public:
        explicit ImageTextureSource(boost::intrusive_ptr<Image> image) :
            image_(image)
        { }

        bool isValid() const
        {
            return true;
        }

        void create()
        { }

        void destroy()
        { }

        GLsizei getWidth() const
        {
            return image_->getWidth();
        }

        GLsizei getHeight() const
        {
            return image_->getHeight();
        }

        GLvoid const *getData() const
        {
            return image_->getData();
        }

    private:
        boost::intrusive_ptr<Image> image_;
    };

    std::auto_ptr<TextureSource>
    createImageTextureSource(boost::intrusive_ptr<Image> image)
    {
        return std::auto_ptr<TextureSource>(new ImageTextureSource(image));
    }
}
