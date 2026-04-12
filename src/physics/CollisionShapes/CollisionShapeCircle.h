//
// Created by simon on 4/12/26.
//

#ifndef COLLISIONSHAPECIRCLE_H
#define COLLISIONSHAPECIRCLE_H
#include "CollisionShape.h"

namespace Physics {
    class CollisionShapeCircle : public CollisionShape {
    public:
        CollisionShapeCircle(Vector2 center, float radius)
            : m_center{center}, m_radius{radius} {}

        AABB getAABB() const override;
        Vector2 getCenter() const override {return m_center;}
        float getRadius() const {return m_radius;}

    private:
        Vector2 m_center {};
        float   m_radius {};
    };
}

#endif //COLLISIONSHAPECIRCLE_H
