//
// Created by simon on 4/12/26.
//

#include "CollisionShapeRectangle.h"

#include <algorithm>
#include <cfloat>
#include <cmath>

namespace Physics {
    AABB CollisionShapeRectangle::getAABB() const {
        // The 4 corners in local space
        Vector2 corners[4] {
            { -m_halfWidth, -m_halfHeight },
            {  m_halfWidth, -m_halfHeight },
            {  m_halfWidth,  m_halfHeight },
            { -m_halfWidth,  m_halfHeight }
        };

        float minX { FLT_MAX };
        float minY { FLT_MAX };
        float maxX { -FLT_MAX };
        float maxY { -FLT_MAX };

        for (const Vector2& corner : corners) {
            // Rotate each corner by m_rotation into world space
            Vector2 rotated {
                corner.x * cosf(m_rotation) - corner.y * sinf(m_rotation) + m_center.x,
                corner.x * sinf(m_rotation) + corner.y * cos(m_rotation) + m_center.y
            };

            minX = std::min(minX, rotated.x);
            minY = std::min(minY, rotated.y);
            maxX = std::max(maxX, rotated.x);
            maxY = std::max(maxY, rotated.y);
        }

        return { { minX, minY }, { maxX, maxY } };
    }
} // Physics