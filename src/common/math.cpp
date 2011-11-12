#include "math.hpp"

namespace mortified {
    std::ostream &operator<<(std::ostream &out, Vector2 const &v)
    {
        return out << "[" << v.x << ", " << v.y << "]";
    }

    float Matrix3::rotation() const
    {
        Vector2 v = (*this * Vector2(1.0f, 0.0f) -
                     *this * Vector2(0.0f, 0.0f));
        return std::atan2(v.y, v.x);
    }

    float Matrix3::scale() const
    {
        return distance(*this * Vector2(0.0f, 0.0f),
                        *this * Vector2(1.0f, 0.0f));
    }
}
