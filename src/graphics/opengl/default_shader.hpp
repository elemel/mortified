#ifndef MORTIFIED_DEFAULT_SHADER_HPP
#define MORTIFIED_DEFAULT_SHADER_HPP

#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class Context;
    class Shader;

    boost::intrusive_ptr<Shader>
    createShader(boost::intrusive_ptr<Context> context);
}

#endif
