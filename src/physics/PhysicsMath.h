//
// Created by simon on 4/11/26.
//

#ifndef PHYSICSMATH_H
#define PHYSICSMATH_H
#include <raylib.h>

inline float cross2D(Vector2 r, Vector2 f) {
    return r.x * f.y - r.y * f.x;
}

#endif //PHYSICSMATH_H
