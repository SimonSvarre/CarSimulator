//
// Created by simon on 4/11/26.
//

#ifndef PHYSICSMATH_H
#define PHYSICSMATH_H
#include <raylib.h>
#include "raymath.h"

namespace Physics
{

inline constexpr float GRAVITY = 980.0f;

inline float cross2D(Vector2 r, Vector2 f) {
    return r.x * f.y - r.y * f.x;
}

/// Converts angular velocity to linear tangential velocity at a given offset
inline Vector2 angularToLinear(float angularVel, Vector2 offset) {
    return { -angularVel * offset.y, angularVel * offset.x };
}

namespace MomentOfInertia {

    /// Solid rectangle rotating around its center
    /// @param mass Mass in kilograms
    /// @param width Full width in metres
    /// @param height Full height in metres
    inline float rectangle(float mass, float width, float height) {
        return (mass * (width * width + height * height)) / 12.f;
    }

    /// Solid circle rotating around its center
    /// @param mass Mass in kilograms
    /// @param radius Radius in metres
    inline float solidCircle(float mass, float radius) {
        return 0.5f * mass * radius * radius;
    }

    /// Hollow circle (ring) rotating around its center
    /// @param mass Mass in kilograms
    /// @param radius Radius in metres
    inline float hollowCircle(float mass, float radius) {
        return mass * radius * radius;
    }

    /// Solid triangle rotating around its center of mass
    /// @param mass Mass in kilograms
    /// @param base Base width in metres
    /// @param height Height in metres
    inline float triangle(float mass, float base, float height) {
        return (mass * (base * base + height * height)) / 18.f;
    }

    /// Point mass at a given distance from the axis (parallel axis theorem)
    /// Use this to offset any of the above from a different pivot point
    /// @param mass Mass in kilograms
    /// @param baseMoI Moment of inertia around the center of mass
    /// @param distance Distance from center of mass to new pivot
    inline float parallelAxis(float mass, float baseMoI, float distance) {
        return baseMoI + mass * distance * distance;
    }

} // namespace MomentOfInertia

}

#endif //PHYSICSMATH_H
