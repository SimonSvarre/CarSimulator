//
// Created by simon on 4/12/26.
//
// CollisionShape.h
#ifndef COLLISIONSHAPE_H
#define COLLISIONSHAPE_H
#include <raylib.h>

namespace Physics {

    struct AABB {
        Vector2 min;
        Vector2 max;
    };

    enum class ShapeType { Circle, Rectangle };

    class CollisionShape {
    public:
        virtual ~CollisionShape() = default;
        virtual AABB      getAABB()     const = 0;
        virtual ShapeType getType()     const = 0;
        virtual Vector2   getCenter()   const = 0;
        virtual void setCenter(Vector2 center) = 0;
        float getRotation() const {return m_rotation;}
        void setRotation(float angle) {m_rotation = angle;};

    protected:
        float m_rotation {0};
    };

} // namespace Physics
#endif