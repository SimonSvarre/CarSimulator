//
// Created by simon on 4/12/26.
//

#include "CollisionShapeRectangle.h"

namespace Physics {
    // CollisionShapeRectangle.cpp
    AABB CollisionShapeRectangle::getAABB() const {
        return {
            { m_center.x - m_halfWidth, m_center.y - m_halfHeight },
            { m_center.x + m_halfWidth, m_center.y + m_halfHeight }
        };
    }
} // Physics