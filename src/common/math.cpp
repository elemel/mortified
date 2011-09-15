#include "math.hpp"

namespace mortified {
    std::ostream &operator<<(std::ostream &out, Vector2 const &v)
    {
        return out << "[" << v.x << ", " << v.y << "]";
    }

    float Matrix3::scale() const
    {
        return distance(*this * Vector2(0.0f, 0.0f),
                        *this * Vector2(0.0f, 1.0f));
    }
}
