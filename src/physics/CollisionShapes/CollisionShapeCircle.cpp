//
// Created by simon on 4/12/26.
//

#include "CollisionShapeCircle.h"

namespace Physics {
    AABB CollisionShapeCircle::getAABB() const {
        return {
            { m_center.x - m_radius, m_center.y - m_radius },
            { m_center.x + m_radius, m_center.y + m_radius }
        };
    }
}