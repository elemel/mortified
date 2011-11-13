#ifndef MORTIFIED_MATH_IO_HPP
#define MORTIFIED_MATH_IO_HPP

#include "math.hpp"

#include <iostream>

namespace mortified {
    inline std::ostream &operator<<(std::ostream &out, Vector2 const &v)
    {
        return out << "[" << v.x << ", " << v.y << "]";
    }
    
}

#endif
