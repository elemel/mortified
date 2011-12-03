#include "default_program.hpp"

#include "context.hpp"
#include "graphics_resource_base.hpp"
#include "program.hpp"
#include "shader.hpp"

#include <stdexcept>
#include <vector>
#include <SDL/SDL_opengl.h>

namespace mortified {
    class DefaultProgram :
        public virtual Program,
        private virtual GraphicsResourceBase
    {
    public:
        explicit DefaultProgram(boost::intrusive_ptr<Context> context) :
            name_(0)
        {
            addParent(context);
        }

        ~DefaultProgram()
        {
            if (name_) {
                glDeleteProgram(name_);
            }
        }

        GLuint getName() const
        {
            return name_;
        }

        bool isValid() const
        {
            return name_ != 0;
        }

        void attachShader(boost::intrusive_ptr<Shader> shader)
        {
            shaders_.push_back(shader);
            addParent(shader);
        }

        void bind()
        {
            if (name_ == 0) {
                throw std::runtime_error("Must create program before binding it.");
            }
            glUseProgram(name_);
        }
        
        void unbind()
        {
            glUseProgram(0);
        }
        
    private:
        ShaderList shaders_;
        GLuint name_;
        std::vector<char> infoLog_;

        void createImpl()
        {
            createShaders();
            name_ = glCreateProgram();
            handleNameError();
            attachShadersImpl();
            glLinkProgram(name_);
            handleLinkError();
        }
        
        void destroyImpl()
        {
            glDeleteProgram(name_);
            name_ = 0;
        }
        
        void invalidateImpl()
        {
            name_ = 0;
        }

        void createShaders()
        {
            for (ShaderIterator i = shaders_.begin(); i != shaders_.end(); ++i)
            {
                (*i)->create();
            }
        }
        
        void handleNameError()
        {
            if (name_ == 0) {
                throw std::runtime_error("Failed to allocate program name.");
            }
        }

        void attachShadersImpl()
        {
            for (ShaderIterator i = shaders_.begin(); i != shaders_.end(); ++i)
            {
                glAttachShader(name_, (*i)->getName());
            }
        }
        
        void handleLinkError()
        {
            if (!getLinkStatus()) {
                std::vector<char> infoLog;
                getInfoLog(&infoLog);
                glDeleteProgram(name_);
                name_ = 0;
                throw std::runtime_error(std::string("Failed to link program: ") +
                                         &infoLog[0]);
            }
        }

        bool getLinkStatus()
        {
            GLint linkStatus = GL_FALSE;
            glGetProgramiv(name_, GL_LINK_STATUS, &linkStatus);
            return linkStatus == GL_TRUE;
        }

        void getInfoLog(std::vector<char> *infoLog)
        {
            GLint length = 0;
            glGetProgramiv(name_, GL_INFO_LOG_LENGTH, &length);
            if (length) {
                infoLog->resize(length);
                glGetProgramInfoLog(name_, infoLog->size(), 0, &(*infoLog)[0]);
            } else {
                infoLog->assign(1, 0);
            }
        }
    };

    boost::intrusive_ptr<Program>
    createProgram(boost::intrusive_ptr<Context> context)
    {
        return boost::intrusive_ptr<Program>(new DefaultProgram(context));
    }
}
