#include "file_shader_source.hpp"

#include "shader_source.hpp"

#include <stdexcept>
#include <vector>

namespace mortified {
    namespace {
        char const *getFileExt(char const *file)
        {
            std::size_t size = std::strlen(file);
            if (size == 0) {
                return file;
            }
            char const *ext = file + size - 1;
            while (ext != file && *ext != '.') {
                --ext;
            }
            return ext;
        }

        // TODO: Proper implementation.
        GLenum getShaderTypeFromFile(char const *file)
        {
            char const *ext = getFileExt(file);
            if (std::strcmp(ext, ".frag") == 0 ||
                std::strcmp(ext, ".fsh") == 0 ||
                std::strcmp(ext, ".fs") == 0)
            {
                return GL_FRAGMENT_SHADER;
            }
            if (std::strcmp(ext, ".vert") == 0 ||
                std::strcmp(ext, ".vsh") == 0 ||
                std::strcmp(ext, ".vs") == 0)
            {
                return GL_VERTEX_SHADER;
            }
            throw std::runtime_error(std::string("Failed to deduce shader type from file: ") + file);
        }
    }

    class FileShaderSource : public virtual ShaderSource {
    public:
        explicit FileShaderSource(char const *file) :
            file_(file),
            type_(getShaderTypeFromFile(file))
        { }

        bool isValid() const
        {
            return !data_.empty();
        }
        
        void create()
        {
            if (data_.empty()) {
                FILE *stream = fopen(file_, "rb");
                if (stream == 0) {
                    throw std::runtime_error(std::string("Failed to open file: ") + file_);
                }
                try {
                    fseek(stream, 0, SEEK_END);
                    long size = ftell(stream);
                    fseek(stream, 0, SEEK_SET);
                    data_.resize(size + 1);
                    int readSize = fread(&data_[0], 1, size, stream);
                    if (readSize != size) {
                        throw std::runtime_error(std::string("Failed to read file: ") + file_);
                    }
                    data_.back() = 0;
                } catch (...) {
                    fclose(stream);
                    data_.clear();
                    throw;
                }
                fclose(stream);
            }
        }

        void destroy()
        {
            data_.clear();
        }

        GLenum getType() const
        {
            return type_;
        }

        GLint getSize() const
        {
            if (data_.empty()) {
                throw std::runtime_error("Must create source before getting size.");
            }
            return data_.size() - 1;
        }

        GLchar const *getData() const
        {
            if (data_.empty()) {
                throw std::runtime_error("Must create source before getting data.");
            }
            return &data_[0];
        }

    private:
        char const *file_;
        GLenum type_;
        std::vector<char> data_;
    };
    
    std::auto_ptr<ShaderSource> createFileShaderSource(char const *file)
    {
        return std::auto_ptr<ShaderSource>(new FileShaderSource(file));
    }
}
