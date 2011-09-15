#include "geometry.hpp"

#include <algorithm>
#include <cmath>
#include <limits>

namespace mortified {
    void Circle2::transform(Matrix3 const &m)
    {
        center = m * center;
        radius *= m.scale();
    }

    Polygon2::Polygon2(Box2 const &b)
    {
        vertices.push_back(b.p1);
        vertices.push_back(Vector2(b.p2.x, b.p1.y)); 
        vertices.push_back(b.p2);
        vertices.push_back(Vector2(b.p1.x, b.p2.y)); 
    }

    Polygon2::Polygon2(Circle2 const &c, int size, float angle)
    {
        vertices.resize(size);
        for (int i = 0; i < size; ++i) {
            float a = angle + 2.0f * pi * float(i) / float(size);
            vertices[i] = c.center + c.radius * Vector2(std::cos(a), std::sin(a));
        }
    }

    void Polygon2::transform(Matrix3 const &m)
    {
        for (std::vector<Vector2>::iterator i = vertices.begin();
             i != vertices.end(); ++i)
        {
            *i = m * *i;
        }
    }

    bool intersects(Box2 const &b, Circle2 const &c)
    {
        if (b.p1.x <= c.center.x && c.center.x <= b.p2.x) {
            return (b.p1.y <= c.center.y + c.radius &&
                    c.center.y - c.radius <= b.p2.y);
        } else if (b.p1.y <= c.center.y && c.center.y <= b.p2.y) {
            return (b.p1.x <= c.center.x + c.radius &&
                    c.center.x - c.radius <= b.p2.x);
        } else {
            return (intersects(c, b.p1) ||
                    intersects(c, Vector2(b.p2.x, b.p1.y)) ||
                    intersects(c, b.p2) ||
                    intersects(c, Vector2(b.p1.x, b.p2.y)));
        }
    }
}
