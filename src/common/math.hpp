#ifndef MORTIFIED_MATH_HPP
#define MORTIFIED_MATH_HPP

#include <cmath>
#include <iostream>
#include <vector>

namespace mortified {
    const float pi = 3.14159265358979323846264338327950288419716939937510f;

    inline bool finite(float f)
    {
        return std::abs(f) <= std::numeric_limits<float>::max();
    }

    inline float sign(float f)
    {
        return f < 0.0f ? -1.0f : 1.0f;
    }

    inline float square(float f)
    {
        return f * f;
    }

    inline float clamp(float f, float minValue, float maxValue)
    {
        return std::min(std::max(f, minValue), maxValue);
    }

    class Vector2 {
    public:
        float x, y;

        Vector2();
        explicit Vector2(float f);
        Vector2(float x, float y);

        float length() const;
        float squaredLength() const;

        Vector2 operator-() const;

        Vector2 &operator+=(Vector2 const &v);
        Vector2 &operator-=(Vector2 const &v);
        Vector2 &operator*=(float f);
        Vector2 &operator/=(float f);

        float normalize();
        void clampLength(float maxLength);
    };

    inline Vector2::Vector2() :
        x(0.0f), y(0.0f)
    { }

    inline Vector2::Vector2(float f) :
        x(f), y(f)
    { }

    inline Vector2::Vector2(float x, float y) :
        x(x), y(y)
    { }

    inline float Vector2::length() const
    {
        return std::sqrt(squaredLength());
    }

    inline float Vector2::squaredLength() const
    {
        return square(x) + square(y);
    }

    inline Vector2 Vector2::operator-() const
    {
        return Vector2(-x, -y);
    }

    inline Vector2 &Vector2::operator+=(Vector2 const &v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    inline Vector2 &Vector2::operator-=(Vector2 const &v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    inline Vector2 &Vector2::operator*=(float f)
    {
        x *= f;
        y *= f;
        return *this;
    }

    inline Vector2 &Vector2::operator/=(float f)
    {
        x /= f;
        y /= f;
        return *this;
    }

    inline float Vector2::normalize()
    {
        float f = squaredLength();
        if (f != 0.0f && f != 1.0f) {
            f = std::sqrt(f);
            *this /= f;
        }
        return f;
    }

    inline void Vector2::clampLength(float maxLength)
    {
        if (squaredLength() > square(maxLength)) {
            normalize();
            *this *= maxLength;
        }
    }

    inline Vector2 operator+(Vector2 const &v1, Vector2 const &v2)
    {
        return Vector2(v1) += v2;
    }

    inline Vector2 operator-(Vector2 const &v1, Vector2 const &v2)
    {
        return Vector2(v1) -= v2;
    }

    inline Vector2 operator*(Vector2 const &v, float f)
    {
        return Vector2(v) *= f;
    }

    inline Vector2 operator*(float f, Vector2 const &v)
    {
        return Vector2(v) *= f;
    }

    inline Vector2 operator/(Vector2 const &v, float f)
    {
        return Vector2(v) /= f;
    }

    inline float dot(Vector2 const &v1, Vector2 const &v2)
    {
        return v1.x * v2.x + v1.y * v2.y;
    }

    inline float cross(Vector2 const &v1, Vector2 const &v2)
    {
        return v1.x * v2.y - v2.x * v1.y;
    }

    inline Vector2 cross(Vector2 const &v)
    {
        return Vector2(-v.y, v.x);
    }

    inline Vector2 normalize(Vector2 const &v)
    {
        Vector2 result(v);
        result.normalize();
        return result;
    }

    inline Vector2 clampLength(Vector2 const &v, float maxLength)
    {
        Vector2 result(v);
        result.clampLength(maxLength);
        return result;
    }

    inline float distance(Vector2 const &p1, Vector2 const &p2)
    {
        return (p2 - p1).length();
    }

    inline float squaredDistance(Vector2 const &p1, Vector2 const &p2)
    {
        return (p2 - p1).squaredLength();
    }

    std::ostream &operator<<(std::ostream &out, Vector2 const &v);

    class Matrix3 {
    public:
        float a, b, c;
        float d, e, f;
        float g, h, i;

        Matrix3();
        explicit Matrix3(float x);
        Matrix3(float a, float b, float c,
                float d, float e, float f);
        Matrix3(float a, float b, float c,
                float d, float e, float f,
                float g, float h, float i);

        float scale() const;

        Matrix3 &operator+=(Matrix3 const &m);
        Matrix3 &operator-=(Matrix3 const &m);
        Matrix3 &operator*=(Matrix3 const &m);
        Matrix3 &operator*=(float x);
        Matrix3 &operator/=(float x);

        void transpose();

        void translate(Vector2 const &v);
        void scale(float x);
        void scale(Vector2 const &v);
        void rotate(float x);
    };

    inline Matrix3::Matrix3() :
        a(1.0f), b(0.0f), c(0.0f),
        d(0.0f), e(1.0f), f(0.0f),
        g(0.0f), h(0.0f), i(1.0f)
    { }

    inline Matrix3::Matrix3(float x) :
        a(x), b(x), c(x),
        d(x), e(x), f(x),
        g(x), h(x), i(x)
    { }

    inline Matrix3::Matrix3(float a, float b, float c,
                            float d, float e, float f) :
        a(a), b(b), c(c),
        d(d), e(e), f(f),
        g(0.0f), h(0.0f), i(1.0f)
    { }

    inline Matrix3::Matrix3(float a, float b, float c,
                            float d, float e, float f,
                            float g, float h, float i) :
        a(a), b(b), c(c),
        d(d), e(e), f(f),
        g(g), h(h), i(i)
    { }

    inline Matrix3 &Matrix3::operator+=(Matrix3 const &m)
    {
        a += m.a;
        b += m.b;
        c += m.c;

        d += m.d;
        e += m.e;
        f += m.f;

        g += m.g;
        h += m.h;
        i += m.i;

        return *this;
    }

    inline Matrix3 &Matrix3::operator-=(Matrix3 const &m)
    {
        a -= m.a;
        b -= m.b;
        c -= m.c;

        d -= m.d;
        e -= m.e;
        f -= m.f;

        g -= m.g;
        h -= m.h;
        i -= m.i;

        return *this;
    }

    inline Matrix3 &Matrix3::operator*=(float x)
    {
        a *= x;
        b *= x;
        c *= x;

        d *= x;
        e *= x;
        f *= x;

        g *= x;
        h *= x;
        i *= x;

        return *this;
    }

    inline Matrix3 &Matrix3::operator/=(float x)
    {
        return *this *= 1.0f / x;
    }

    inline void Matrix3::transpose()
    {
        std::swap(d, b);
        std::swap(g, c);
        std::swap(h, f);
    }

    inline void Matrix3::translate(Vector2 const &v)
    {
        *this *= Matrix3(1.0f, 0.0f, v.x, 0.0f, 1.0f, v.y);
    }

    inline void Matrix3::scale(float x)
    {
        *this *= Matrix3(x, 0.0f, 0.0f, 0.0f, x, 0.0f);
    }

    inline void Matrix3::scale(Vector2 const &v)
    {
        *this *= Matrix3(v.x, 0.0f, 0.0f, 0.0f, v.y, 0.0f);
    }

    inline void Matrix3::rotate(float x)
    {
        float sx = std::sin(x);
        float cx = std::cos(x);
        *this *= Matrix3(cx, -sx, 0.0f, sx, cx, 0.0f);
    }

    inline Matrix3 operator*(Matrix3 const &m1, Matrix3 const &m2)
    {
        return Matrix3(m1.a * m2.a + m1.b * m2.d + m1.c * m2.g,
                       m1.a * m2.b + m1.b * m2.e + m1.c * m2.h,
                       m1.a * m2.c + m1.b * m2.f + m1.c * m2.i,

                       m1.d * m2.a + m1.e * m2.d + m1.f * m2.g,
                       m1.d * m2.b + m1.e * m2.e + m1.f * m2.h,
                       m1.d * m2.c + m1.e * m2.f + m1.f * m2.i,

                       m1.g * m2.a + m1.h * m2.d + m1.i * m2.g,
                       m1.g * m2.b + m1.h * m2.e + m1.i * m2.h,
                       m1.g * m2.c + m1.h * m2.f + m1.i * m2.i);
    }

    inline Matrix3 &Matrix3::operator*=(Matrix3 const &m)
    {
        return *this = *this * m;
    }

    inline Vector2 operator*(Matrix3 const &m, Vector2 const &p)
    {
        return Vector2(m.a * p.x + m.b * p.y + m.c,
                       m.d * p.x + m.e * p.y + m.f);
    }
}

#endif
