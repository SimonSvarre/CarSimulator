//
// Created by simon on 4/12/26.
//

#ifndef COLLISIONDETECTOR_H
#define COLLISIONDETECTOR_H

#include "CollisionManifold.h"
#include "../CollisionShapes/CollisionShape.h"
#include "../CollisionShapes/CollisionShapeRectangle.h"
#include "../CollisionShapes/CollisionShapeCircle.h"

namespace Physics {

    ///shape vs shape tests
class CollisionDetector {
public:
    /// Entry point — dispatches to the correct test based on shape types
    static CollisionManifold test(const CollisionShape* a, const CollisionShape* b);

    static bool aabbOverlap(const AABB& a, const AABB& b);

private:
    static CollisionManifold testCircleCircle(const CollisionShape* a, const CollisionShape* b);
    static CollisionManifold testRectRect    (const CollisionShape* a, const CollisionShape* b);
    static CollisionManifold testCircleRect  (const CollisionShape* circle, const CollisionShape* rect);

    static float projectRect(const CollisionShapeRectangle* rect, Vector2 axis)
};

} // Physics

#endif //COLLISIONDETECTOR_H
