#ifndef MORTIFIED_GEOMETRY_HPP
#define MORTIFIED_GEOMETRY_HPP

#include "math.hpp"

#include <cmath>
#include <iostream>
#include <vector>

namespace mortified {
    class Box2 {
    public:
        Vector2 p1, p2;

        Box2();
        Box2(Vector2 const &p1, Vector2 const &p2);

        Vector2 center() const;
        bool empty() const;
        float dx() const;
        float dy() const;
        float perimeter() const;
        float area() const;

        void clear();
        void merge(Vector2 const &p);
        void merge(Box2 const &b);
    };

    inline Box2::Box2()
    { }

    inline Box2::Box2(Vector2 const &p1, Vector2 const &p2) :
        p1(p1),
        p2(p2)
    { }

    inline Vector2 Box2::center() const
    {
        return Vector2(0.5f * (p1.x + p2.x), 0.5f * (p1.y + p2.y));
    }

    inline bool Box2::empty() const
    {
        return dx() <= 0.0f || dy() <= 0.0f;
    }

    inline float Box2::dx() const
    {
        return p2.x - p1.x;
    }

    inline float Box2::dy() const
    {
        return p2.y - p1.y;
    }

    inline float Box2::perimeter() const
    {
        return 2.0f * (dx() + dy());
    }

    inline float Box2::area() const
    {
        return dx() * dy();
    }

    inline void Box2::clear()
    {
        p1.x = std::numeric_limits<float>::max();
        p1.y = std::numeric_limits<float>::max();
        p2.x = std::numeric_limits<float>::min();
        p2.y = std::numeric_limits<float>::min();
    }

    inline void Box2::merge(Vector2 const &p)
    {
        p1.x = std::min(p1.x, p.x);
        p1.y = std::min(p1.y, p.y);
        p2.x = std::max(p2.x, p.x);
        p2.y = std::max(p2.y, p.y);
    }

    inline void Box2::merge(const Box2 &b)
    {
        p1.x = std::min(p1.x, b.p1.x);
        p1.y = std::min(p1.y, b.p1.y);
        p2.x = std::max(p2.x, b.p2.x);
        p2.y = std::max(p2.y, b.p2.y);
    }

    inline Box2 intersect(const Box2 &b1, const Box2 &b2)
    {
        float x1 = std::max(b1.p1.x, b2.p1.x);
        float y1 = std::max(b1.p1.y, b2.p1.y);
        float x2 = std::min(b1.p2.x, b2.p2.x);
        float y2 = std::min(b1.p2.y, b2.p2.y);
        return Box2(Vector2(x1, y1), Vector2(x2, y2));
    }

    class LineSegment2 {
    public:
        Vector2 p1, p2;

        LineSegment2();
        LineSegment2(Vector2 const &p1, Vector2 const &p2);

        float length() const;
        float squaredLength() const;
        Box2 boundingBox() const;
    };

    inline LineSegment2::LineSegment2()
    { }

    inline LineSegment2::LineSegment2(Vector2 const &p1, Vector2 const &p2) :
        p1(p1),
        p2(p2)
    { }

    inline float LineSegment2::length() const
    {
        return distance(p1, p2);
    }

    inline float LineSegment2::squaredLength() const
    {
        return squaredDistance(p1, p2);
    }

    inline Box2 LineSegment2::boundingBox() const
    {
        return Box2(Vector2(std::min(p1.x, p2.x), std::min(p1.y, p2.y)),
                    Vector2(std::max(p1.x, p2.x), std::max(p1.y, p2.y)));
    }

    class Circle2 {
    public:
        Vector2 center;
        float radius;

        Circle2();
        Circle2(Vector2 const &center, float radius);

        float perimeter() const;
        float area() const;
        Box2 boundingBox() const;

        void transform(Matrix3 const &m);
    };

    inline Circle2::Circle2() :
        radius(0.0f)
    { }

    inline Circle2::Circle2(Vector2 const &center, float radius) :
        center(center),
        radius(radius)
    { }

    inline float Circle2::perimeter() const
    {
        return 2.0f * pi * radius;
    }

    inline float Circle2::area() const
    {
        return pi * square(radius);
    }

    inline Box2 Circle2::boundingBox() const
    {
        return Box2(center - Vector2(radius), center + Vector2(radius));
    }

    inline Circle2 transform(Circle2 const &c, Matrix3 const &m)
    {
        Circle2 result(c);
        result.transform(m);
        return result;
    }

    class Polygon2 {
    public:
        std::vector<Vector2> vertices;

        Polygon2();
        explicit Polygon2(Box2 const &b);
        Polygon2(Circle2 const &c, int size, float angle = 0.0f);

        bool empty() const;
        int size() const;
        bool clockwise() const;

        void reverse();
        void transform(Matrix3 const &m);
    };

    inline Polygon2::Polygon2()
    { }

    inline bool Polygon2::empty() const
    {
        return vertices.empty();
    }

    inline int Polygon2::size() const
    {
        return vertices.size();
    }

    inline bool Polygon2::clockwise() const
    {
        return (vertices.size() >= 3 &&
                cross(vertices[1] - vertices[0],
                      vertices[2] - vertices[1]) <= 0.0f);
    }

    inline void Polygon2::reverse()
    {
        std::reverse(vertices.begin(), vertices.end());
    }

    inline Polygon2 transform(Polygon2 const &p, Matrix3 const &m)
    {
        Polygon2 result(p);
        result.transform(m);
        return result;
    }

    inline bool intersects(Vector2 const &p1, Vector2 const &p2)
    {
        (void) p1;
        (void) p2;
        return false;
    }

    inline bool intersects(Box2 const &b1, Box2 const &b2)
    {
        return (b1.p1.x <= b2.p2.x && b2.p1.x <= b1.p2.x &&
                b1.p1.y <= b2.p2.y && b2.p1.y <= b1.p2.y);
    }

    inline bool intersects(Box2 const &b, Vector2 const &p)
    {
        return (b.p1.x <= p.x && p.x <= b.p2.x &&
                b.p1.y <= p.y && p.y <= b.p2.y);
    }

    bool intersects(Box2 const &b, Circle2 const &c);

    inline bool intersects(Circle2 const &c1, Circle2 const &c2)
    {
        return (squaredDistance(c1.center, c2.center) <=
                square(c1.radius + c2.radius));
    }

    inline bool intersects(Circle2 const &c, Vector2 const &p)
    {
        return squaredDistance(c.center, p) <= square(c.radius);
    }

    inline bool intersects(Vector2 const &p, Box2 const &b)
    {
        return intersects(b, p);
    }

    inline bool intersects(Vector2 const &p, Circle2 const &c)
    {
        return intersects(c, p);
    }

    inline bool intersects(Circle2 const &c, Box2 const &b)
    {
        return intersects(b, c);
    }
}

#endif
