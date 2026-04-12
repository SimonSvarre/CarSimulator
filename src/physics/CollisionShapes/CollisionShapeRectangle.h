//
// Created by simon on 4/12/26.
//

// CollisionShapeRectangle.h
#ifndef COLLISIONSHAPECIRCLERECTANGLE_H
#define COLLISIONSHAPECIRCLERECTANGLE_H
#include "CollisionShape.h"

namespace Physics {

    class CollisionShapeRectangle : public CollisionShape {
    public:
        CollisionShapeRectangle(Vector2 center, float width, float height)
            : m_center{center}, m_halfWidth{width / 2.f}, m_halfHeight{height / 2.f} {}

        AABB      getAABB()      const override;
        ShapeType getType()      const override { return ShapeType::Rectangle; }
        Vector2   getCenter()    const override { return m_center; }
        float     getHalfWidth() const          { return m_halfWidth; }
        float     getHalfHeight()const          { return m_halfHeight; }

    private:
        Vector2 m_center     {};
        float   m_halfWidth  {};
        float   m_halfHeight {};
    };

} // namespace Physics
#endif
