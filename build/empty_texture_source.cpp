#include "empty_texture_source.hpp"

#include "texture_source.hpp"

namespace mortified {
    class EmptyTextureSource : public virtual TextureSource {
    public:
        EmptyTextureSource(int width, int height) :
            width_(width),
            height_(height)
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
            return width_;
        }
        
        int height() const
        {
            return height_;
        }
        
        void const *pixels() const
        {
            return 0;
        }
        
    private:
        int width_;
        int height_;
    };

    boost::shared_ptr<TextureSource>
        createEmptyTextureSource(int width, int height)
    {
        return boost::shared_ptr<TextureSource>(new EmptyTextureSource(width, height));
    }
}
