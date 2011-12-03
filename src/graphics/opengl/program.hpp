#ifndef MORTIFIED_PROGRAM_HPP
#define MORTIFIED_PROGRAM_HPP

#include "graphics_resource.hpp"

#include <list>
#include <boost/intrusive_ptr.hpp>
#include <SDL/SDL_opengl.h>

namespace mortified {
    class Shader;

    class Program : public virtual GraphicsResource {
    public:
        typedef boost::intrusive_ptr<Shader> ShaderPtr;
        typedef std::list<ShaderPtr> ShaderList;
        typedef ShaderList::iterator ShaderIterator;
        typedef ShaderList::const_iterator ConstShaderIterator;

        virtual GLuint getName() const = 0;

        virtual void attachShader(boost::intrusive_ptr<Shader> shader) = 0;

        virtual void bind() = 0;
        virtual void unbind() = 0;
    };
}

#endif
