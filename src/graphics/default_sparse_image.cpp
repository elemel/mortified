#include "default_sparse_image.hpp"

#include "color.hpp"
#include "ref_counted_base.hpp"
#include "sparse_image.hpp"

#include <elemel/flat_map.hpp>
#include <SDL/SDL_opengl.h>

namespace mortified {
    class DefaultSparseImage :
        public virtual SparseImage,
        private virtual RefCountedBase
    {
    public:
        typedef std::pair<short, short> Key;
        typedef elemel::flat_map<Key, Color4> PixelMap;
        typedef PixelMap::iterator PixelIterator;
        typedef PixelMap::const_iterator ConstPixelIterator;
        
        DefaultSparseImage() :
            minX_(0),
            minY_(0),
            maxX_(0),
            maxY_(0)
        { }

        int getX() const
        {
            return minX_;
        }

        int getY() const
        {
            return minY_;
        }

        int getWidth() const
        {
            return maxX_ - minX_ + 1;
        }

        int getHeight() const
        {
            return maxY_ - minY_ + 1;
        }
        
        Color4 getPixel(int x, int y) const
        {
            ConstPixelIterator i = pixels_.find(Key(y, x));
            return (i == pixels_.end()) ? Color4(0, 0, 0, 0) : i->second;
        }

        void setPixel(int x, int y, Color4 color)
        {
            pixels_[Key(y, x)] = color;
            if (pixels_.size() == 1) {
                minX_ = x;
                minY_ = y;
                maxX_ = x;
                maxY_ = y;
            } else {
                minX_ = std::min(x, minX_);
                minY_ = std::min(y, minY_);
                maxX_ = std::max(x, maxX_);
                maxY_ = std::max(y, maxY_);
            }
        }

        int getSize() const
        {
            return pixels_.size();
        }

        Pixel const *getData() const
        {
            return reinterpret_cast<Pixel const *>(pixels_.data());
        }

        void normalize()
        {
            DefaultSparseImage temp;
            for (PixelIterator i = pixels_.begin(); i != pixels_.end(); ++i) {
                Color4 color = i->second;
                if (color.alpha) {
                    Key key = i->first;
                    temp.setPixel(key.second, key.first, color);
                }
            }

            pixels_.swap(temp.pixels_);
            minX_ = temp.minX_;
            minY_ = temp.minY_;
            maxX_ = temp.maxX_;
            maxY_ = temp.maxY_;            
        }

        void draw()
        {
            glBegin(GL_QUADS);
            for (PixelIterator i = pixels_.begin(); i != pixels_.end(); ++i) {
                Key key = i->first;
                int x = key.second;
                int y = key.first;
                Color4 color = i->second;
                glColor4ub(color.red, color.green, color.blue, color.alpha);
                glVertex2i(x, y);
                glVertex2i(x + 1, y);
                glVertex2i(x + 1, y + 1);
                glVertex2i(x, y + 1);
            }
            glEnd();
        }

    private:
        PixelMap pixels_;
        int minX_;
        int minY_;
        int maxX_;
        int maxY_;
    };

    boost::intrusive_ptr<SparseImage> createSparseImage()
    {
        return boost::intrusive_ptr<SparseImage>(new DefaultSparseImage);
    }
}
