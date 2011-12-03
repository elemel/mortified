#ifndef MORTIFIED_FILE_SHADER_SOURCE_HPP
#define MORTIFIED_FILE_SHADER_SOURCE_HPP

#include <memory>

namespace mortified {
    class ShaderSource;

    std::auto_ptr<ShaderSource> createFileShaderSource(char const *file);
}

#endif
