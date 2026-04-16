#pragma once

#include <raylib.h>
#include <cmath>

// ============================================================
//  raylib Vector2 Operator Overloads
//  Include this header after <raylib.h>
// ============================================================


// ─── Arithmetic operators ────────────────────────────────────

inline Vector2 operator+(const Vector2& a, const Vector2& b)  { return { a.x + b.x, a.y + b.y }; }
inline Vector2 operator-(const Vector2& a, const Vector2& b)  { return { a.x - b.x, a.y - b.y }; }
inline Vector2 operator*(const Vector2& a, const Vector2& b)  { return { a.x * b.x, a.y * b.y }; }
inline Vector2 operator/(const Vector2& a, const Vector2& b)  { return { a.x / b.x, a.y / b.y }; }

// Scalar operations
inline Vector2 operator*(const Vector2& v, float s)            { return { v.x * s, v.y * s }; }
inline Vector2 operator*(float s, const Vector2& v)            { return { v.x * s, v.y * s }; }
inline Vector2 operator/(const Vector2& v, float s)            { return { v.x / s, v.y / s }; }

// Unary negation
inline Vector2 operator-(const Vector2& v)                     { return { -v.x, -v.y }; }


// ─── Compound assignment operators ───────────────────────────

inline Vector2& operator+=(Vector2& a, const Vector2& b)  { a.x += b.x; a.y += b.y; return a; }
inline Vector2& operator-=(Vector2& a, const Vector2& b)  { a.x -= b.x; a.y -= b.y; return a; }
inline Vector2& operator*=(Vector2& a, const Vector2& b)  { a.x *= b.x; a.y *= b.y; return a; }
inline Vector2& operator/=(Vector2& a, const Vector2& b)  { a.x /= b.x; a.y /= b.y; return a; }

inline Vector2& operator*=(Vector2& v, float s)           { v.x *= s; v.y *= s; return v; }
inline Vector2& operator/=(Vector2& v, float s)           { v.x /= s; v.y /= s; return v; }


// ─── Comparison operators ─────────────────────────────────────

inline bool operator==(const Vector2& a, const Vector2& b)  { return a.x == b.x && a.y == b.y; }
inline bool operator!=(const Vector2& a, const Vector2& b)  { return !(a == b); }


// ─── Math utilities ───────────────────────────────────────────

// Dot product
inline float dot(const Vector2& a, const Vector2& b)
{
    return a.x * b.x + a.y * b.y;
}

// 2-D "cross product" (scalar z-component of the 3-D cross product)
inline float cross(const Vector2& a, const Vector2& b)
{
    return a.x * b.y - a.y * b.x;
}

// Squared length  (avoids sqrt – useful for comparisons)
inline float lengthSq(const Vector2& v)
{
    return v.x * v.x + v.y * v.y;
}

// Length / magnitude
inline float length(const Vector2& v)
{
    return std::sqrt(lengthSq(v));
}

// Normalize  (returns zero vector if length == 0)
inline Vector2 normalize(const Vector2& v)
{
    float len = length(v);
    if (len == 0.0f) return { 0.0f, 0.0f };
    return v / len;
}

// Distance between two points
inline float distance(const Vector2& a, const Vector2& b)
{
    return length(b - a);
}

// Squared distance  (avoids sqrt)
inline float distanceSq(const Vector2& a, const Vector2& b)
{
    return lengthSq(b - a);
}

// Linear interpolation
inline Vector2 lerp(const Vector2& a, const Vector2& b, float t)
{
    return a + (b - a) * t;
}

// Reflect v around a unit normal n
inline Vector2 reflect(const Vector2& v, const Vector2& n)
{
    return v - n * (2.0f * dot(v, n));
}

// Component-wise absolute value
inline Vector2 abs(const Vector2& v)
{
    return { std::fabs(v.x), std::fabs(v.y) };
}

// Component-wise clamp
inline Vector2 clamp(const Vector2& v, const Vector2& lo, const Vector2& hi)
{
    return {
        v.x < lo.x ? lo.x : (v.x > hi.x ? hi.x : v.x),
        v.y < lo.y ? lo.y : (v.y > hi.y ? hi.y : v.y)
    };
}

// Perpendicular vector (rotated 90° counter-clockwise)
inline Vector2 perp(const Vector2& v)
{
    return { -v.y, v.x };
}

// Rotate v by angle (radians)
inline Vector2 rotate(const Vector2& v, float angle)
{
    float c = std::cos(angle);
    float s = std::sin(angle);
    return { v.x * c - v.y * s, v.x * s + v.y * c };
}

// Angle of vector in radians (atan2)
inline float angle(const Vector2& v)
{
    return std::atan2(v.y, v.x);
}

// Angle between two vectors in radians
inline float angleBetween(const Vector2& a, const Vector2& b)
{
    float d = dot(normalize(a), normalize(b));
    // Clamp to [-1, 1] to guard against floating-point drift
    d = d < -1.0f ? -1.0f : (d > 1.0f ? 1.0f : d);
    return std::acos(d);
}

// Project a onto b
inline Vector2 project(const Vector2& a, const Vector2& b)
{
    float bLenSq = lengthSq(b);
    if (bLenSq == 0.0f) return { 0.0f, 0.0f };
    return b * (dot(a, b) / bLenSq);
}

// ─── Stream output (optional, useful for debugging) ──────────
#ifdef RAYLIB_VECTOR2_STREAM
#include <ostream>
inline std::ostream& operator<<(std::ostream& os, const Vector2& v)
{
    return os << "Vector2(" << v.x << ", " << v.y << ")";
}
#endif // RAYLIB_VECTOR2_STREAM
