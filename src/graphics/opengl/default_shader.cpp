#include "default_shader.hpp"

#include "context.hpp"
#include "graphics_resource_base.hpp"
#include "shader.hpp"
#include "shader_source.hpp"

#include <stdexcept>
#include <vector>
#include <SDL/SDL_opengl.h>

namespace mortified {
    class DefaultShader :
        public virtual Shader,
        private virtual GraphicsResourceBase
    {
    public:
        explicit DefaultShader(boost::intrusive_ptr<Context> context) :
            type_(0),
            name_(0)
        {
            addParent(context);
        }
        
        ~DefaultShader()
        {
            if (name_) {
                glDeleteShader(name_);
            }
        }

        bool isValid() const
        {
            return name_ != 0;
        }

        GLuint getName() const
        {
            return name_;
        }

        void setSource(std::auto_ptr<ShaderSource> source)
        {
            source_ = source;
        }
        
    private:
        GLuint type_;
        GLuint name_;
        std::auto_ptr<ShaderSource> source_;

        void createImpl()
        {
            if (!source_.get()) {
                throw std::runtime_error("Must set source before creating shader.");
            }

            source_->create();

            type_ = source_->getType();
            name_ = glCreateShader(type_);
            handleNameError();
            setSourceImpl();
            glCompileShader(name_);
            handleCompileError();

            source_->destroy();
        }
        
        void destroyImpl()
        {
            glDeleteShader(name_);
            name_ = 0;
        }
        
        void invalidateImpl()
        {
            name_ = 0;
        }

        void handleNameError()
        {
            if (name_ == 0) {
                source_->destroy();
                throw std::runtime_error("Failed to allocate shader name.");
            }
        }

        void setSourceImpl()
        {
            GLint size = source_->getSize();
            GLchar const *data = source_->getData();
            glShaderSource(name_, 1, &data, &size);
        }

        void handleCompileError()
        {
            if (!getCompileStatus()) {
                std::vector<char> infoLog;
                getInfoLog(&infoLog);
                glDeleteShader(name_);
                name_ = 0;
                source_->destroy();
                throw std::runtime_error(std::string("Failed to compile shader: ") +
                                         &infoLog[0]);
            }
        }
        
        bool getCompileStatus()
        {
            GLint compileStatus = GL_FALSE;
            glGetShaderiv(name_, GL_COMPILE_STATUS, &compileStatus);
            return compileStatus == GL_TRUE;
        }

        void getInfoLog(std::vector<char> *infoLog)
        {
            GLint length = 0;
            glGetShaderiv(name_, GL_INFO_LOG_LENGTH, &length);
            if (length) {
                infoLog->resize(length);
                glGetShaderInfoLog(name_, infoLog->size(), 0, &(*infoLog)[0]);
            } else {
                infoLog->assign(1, 0);
            }
        }
    };

    boost::intrusive_ptr<Shader>
    createShader(boost::intrusive_ptr<Context> context)
    {
        return boost::intrusive_ptr<Shader>(new DefaultShader(context));
    }
}
