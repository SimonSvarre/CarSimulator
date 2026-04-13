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
        CollisionShapeRectangle(float width, float height)
            : m_center{0,0}, m_halfWidth{width / 2.f}, m_halfHeight{height / 2.f} {}

        /// returns AABB where m_center is in the center of the rectangle
        AABB      getAABB()      const override;
        ShapeType getType()      const override { return ShapeType::Rectangle; }
        Vector2   getCenter()    const override { return m_center; }
        void setCenter(Vector2 newCenter) override {m_center = newCenter;} // Er det måske fjollet at både rigidbody og shape holder position og sådan
        float     getHalfWidth() const          { return m_halfWidth; }
        float     getHalfHeight()const          { return m_halfHeight; }

    private:
        Vector2 m_center     {};
        float   m_halfWidth  {};
        float   m_halfHeight {};
    };

} // namespace Physics
#endif
