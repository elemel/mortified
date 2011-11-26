#include "sparse_image_vertex_buffer_source.hpp"

#include "sparse_image.hpp"
#include "vertex_buffer_source.hpp"

#include <vector>

namespace mortified {
    class SparseImageVertexBufferSource : public virtual VertexBufferSource {
    public:
        struct Vertex {
            GLshort x;
            GLshort y;
            GLubyte red;
            GLubyte green;
            GLubyte blue;
            GLubyte alpha;
        };

        typedef std::vector<Vertex> VertexVector;
        
        explicit SparseImageVertexBufferSource(boost::intrusive_ptr<SparseImage> image) :
            image_(image),
            valid_(false)
        { }

        bool isValid() const
        {
            return valid_;
        }
        
        void create()
        {
            if (!valid_) {
                int pixelCount = image_->getSize();
                SparseImage::Pixel const *pixelData = image_->getData();
                vertices_.resize(pixelCount * 4);
                for (int i = 0; i < pixelCount; ++i) {
                    SparseImage::Pixel const *pixel = pixelData + i;

                    vertices_[i * 4 + 0].x = pixel->x;
                    vertices_[i * 4 + 0].y = pixel->y;

                    vertices_[i * 4 + 1].x = pixel->x + 1;
                    vertices_[i * 4 + 1].y = pixel->y;

                    vertices_[i * 4 + 2].x = pixel->x + 1;
                    vertices_[i * 4 + 2].y = pixel->y + 1;

                    vertices_[i * 4 + 3].x = pixel->x;
                    vertices_[i * 4 + 3].y = pixel->y + 1;

                    for (int j = 0; j < 4; ++j) {
                        vertices_[i * 4 + j].red = pixel->red;
                        vertices_[i * 4 + j].green = pixel->green;
                        vertices_[i * 4 + j].blue = pixel->blue;
                        vertices_[i * 4 + j].alpha = pixel->alpha;
                    }
                }
                valid_ = true;
            }
        }

        void destroy()
        {
            if (valid_) {
                valid_ = false;
                VertexVector().swap(vertices_);
            }
        }
        
        GLsizei getStride() const
        {
            return 8;
        }

        GLsizei getCount() const
        {
            return vertices_.size();
        }

        GLvoid const *getData() const
        {
            return vertices_.empty() ? 0 : &vertices_[0];
        }
        
        GLint getVertexSize() const
        {
            return 2;
        }

        GLenum getVertexType() const
        {
            return GL_SHORT;
        }

        GLvoid const *getVertexOffset() const
        {
            unsigned char *null = 0;
            return null + 0;
        }
        
        GLint getTexCoordSize() const
        {
            return 0;
        }

        GLenum getTexCoordType() const
        {
            return 0;
        }

        GLvoid const *getTexCoordOffset() const
        {
            return 0;
        }
        
        GLint getColorSize() const
        {
            return 4;
        }

        GLenum getColorType() const
        {
            return GL_UNSIGNED_BYTE;
        }

        GLvoid const *getColorOffset() const
        {
            unsigned char *null = 0;
            return null + 4;
        }

    private:
        boost::intrusive_ptr<SparseImage> image_;
        bool valid_;
        std::vector<Vertex> vertices_;
    };
    
    std::auto_ptr<VertexBufferSource>
    createSparseImageVertexBufferSource(boost::intrusive_ptr<SparseImage> image)
    {
        return std::auto_ptr<VertexBufferSource>(new SparseImageVertexBufferSource(image));
    }
}
