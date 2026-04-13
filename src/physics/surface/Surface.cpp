//
// Created by simon on 4/13/26.
//
#include "Surface.h"

namespace Physics {
    bool Surface::contains(Vector2 point) const {
        AABB aabb {m_shape->getAABB()};
        return (point.x > aabb.min.x &&
            point.x < aabb.max.x &&
            point.y > aabb.min.y &&
            point.y < aabb.max.y);
    }
}
