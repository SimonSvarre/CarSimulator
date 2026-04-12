//
// Created by simon on 4/12/26.
//

#include "CollisionDetector.h"

#include <algorithm>
#include <cfloat>
#include <raymath.h>

namespace Physics {
    CollisionManifold CollisionDetector::test(const CollisionShape *a, const CollisionShape *b) {
        ShapeType aType = a->getType();
        ShapeType bType = b->getType();

        if (aType == ShapeType::Circle && bType == ShapeType::Circle)
            return testCircleCircle(a, b);

        if (aType == ShapeType::Rectangle && bType == ShapeType::Rectangle)
            return testRectRect(a, b);

        if (aType == ShapeType::Circle && bType == ShapeType::Rectangle)
            return testCircleRect(a, b);

        if (aType == ShapeType::Rectangle && bType == ShapeType::Circle)
            return testCircleRect(b, a);

        return {};
    }

    bool CollisionDetector::aabbOverlap(const AABB &a, const AABB &b) {
        float d1x = b.min.x - a.min.x;
        float d1y = b.min.y - a.min.y;
        float d2x = a.min.x - b.min.x;
        float d2y = a.min.y - b.min.y;

        if (d1x > 0.0f || d1y > 0.0f)
            return false;

        if (d2x > 0.0f || d2y > 0.0f)
            return false;

        return true;
    }

    CollisionManifold CollisionDetector::testCircleCircle(const CollisionShape *a, const CollisionShape *b) {
        const auto* circleA {dynamic_cast<const CollisionShapeCircle*>(a)};
        const auto* circleB {dynamic_cast<const CollisionShapeCircle*>(b)};

        Vector2 delta {
            circleB->getCenter().x - circleA->getCenter().x,
            circleB->getCenter().y - circleA->getCenter().y
        };

        float distance    { Vector2Length(delta) };
        float radiiSum    { circleA->getRadius() + circleB->getRadius() };

        if (distance >= radiiSum)
            return {};  // no collision, hasCollision defaults to false

        // Avoid division by zero if circles are exactly on top of each other
        Vector2 normal { distance > 0.f
            ? Vector2Scale(delta, 1.f / distance)   // normalize manually
            : Vector2 {1.f, 0.f}                    // arbitrary direction
        };

        return {
            .hasCollision = true,
            .normal       = normal,
            .depth        = radiiSum - distance,
            .contactPoint = {
                circleA->getCenter().x + normal.x * circleA->getRadius(),
                circleA->getCenter().y + normal.y * circleA->getRadius()
            }
        };
    }

        CollisionManifold CollisionDetector::testRectRect(const CollisionShape *a, const CollisionShape *b) {
            const auto* rectA {dynamic_cast<const CollisionShapeRectangle*>(a)};
            const auto* rectB {dynamic_cast<const CollisionShapeRectangle*>(b)};

        // Get the 4 axes to test (face normals of each rect)
        float rotA { rectA->getRotation() };
        float rotB { rectB->getRotation() };

        Vector2 axesA[2] {
            {  cosf(rotA), sinf(rotA) },   // A's local X axis
            { -sinf(rotA), cosf(rotA) }    // A's local Y axis
        };
        Vector2 axesB[2] {
            {  cosf(rotB), sinf(rotB) },
            { -sinf(rotB), cosf(rotB) }
        };

        float   minDepth { FLT_MAX };
        Vector2 minAxis  {};

        // Test all 4 axes
        for (int i = 0; i < 2; i++) {
            for (const Vector2& axis : { axesA[i], axesB[i] }) {
                // Project both rects onto this axis
                float projA { projectRect(rectA, axis) };
                float projB { projectRect(rectB, axis) };

                // Project center-to-center delta onto axis
                Vector2 delta {
                    rectB->getCenter().x - rectA->getCenter().x,
                    rectB->getCenter().y - rectA->getCenter().y
                };
                float centerDist { fabsf(Vector2DotProduct(delta, axis)) };

                float overlap { projA + projB - centerDist };

                // Gap found on this axis — no collision
                if (overlap <= 0.f)
                    return {};

                if (overlap < minDepth) {
                    minDepth = overlap;
                    minAxis  = axis;
                }
            }
        }

        // Make sure normal points from A to B
        Vector2 delta {
            rectB->getCenter().x - rectA->getCenter().x,
            rectB->getCenter().y - rectA->getCenter().y
        };
        if (Vector2DotProduct(delta, minAxis) < 0.f)
            minAxis = Vector2Negate(minAxis);

        return CollisionManifold {
            true,
            minAxis,
            minDepth,
            {
                rectA->getCenter().x + minAxis.x * minDepth,
                rectA->getCenter().y + minAxis.y * minDepth
            }
            };
        }

        CollisionManifold CollisionDetector::testCircleRect(const CollisionShape *circle, const CollisionShape *rect) {
            const auto* circleShape {dynamic_cast<const CollisionShapeCircle*>(circle)};
            const auto* rectShape {dynamic_cast<const CollisionShapeRectangle*>(rect)};

        float rot { rectShape->getRotation() };

        // Transform circle center into rectangle's local space
        Vector2 delta {
            circleShape->getCenter().x - rectShape->getCenter().x,
            circleShape->getCenter().y - rectShape->getCenter().y
        };

        // Rotate delta by negative rect rotation to get into rect local space
        Vector2 localCircle {
            delta.x * cosf(-rot) - delta.y * sinf(-rot),
            delta.x * sinf(-rot) + delta.y * cosf(-rot)
       };

        // Clamp circle center to rect extents to find closest point on rect
        Vector2 closest {
            std::clamp(localCircle.x, -rectShape->getHalfWidth(),  rectShape->getHalfWidth()),
            std::clamp(localCircle.y, -rectShape->getHalfHeight(), rectShape->getHalfHeight())
        };

        // Distance from circle center to closest point on rect
        Vector2 localDelta  { localCircle.x - closest.x, localCircle.y - closest.y };
        float   distance    { Vector2Length(localDelta) };

        if (distance >= circleShape->getRadius())
            return {};  // no collision

        // Avoid division by zero if circle center is inside rect
        Vector2 localNormal { distance > 0.f
            ? Vector2 { localDelta.x / distance, localDelta.y / distance }
            : Vector2 { 1.f, 0.f }
        };

        // Rotate normal back into world space
        Vector2 worldNormal {
            localNormal.x * cosf(rot) - localNormal.y * sinf(rot),
            localNormal.x * sinf(rot) + localNormal.y * cosf(rot)
        };

        // Contact point is on the surface of the circle facing the rect
        Vector2 contactPoint {
            circleShape->getCenter().x - worldNormal.x * circleShape->getRadius(),
            circleShape->getCenter().y - worldNormal.y * circleShape->getRadius()
        };

        return CollisionManifold {
            true,
            worldNormal,
            circleShape->getRadius() - distance,
            contactPoint
        };
    }

    // Returns the half-extent of the rectangle projected onto the axis
    float CollisionDetector::projectRect(const CollisionShapeRectangle* rect, Vector2 axis) {
        float rot { rect->getRotation() };

        Vector2 localX { cosf(rot), sinf(rot) };
        Vector2 localY { -sinf(rot), cosf(rot) };

        return fabsf(Vector2DotProduct(localX, axis)) * rect->getHalfWidth()
             + fabsf(Vector2DotProduct(localY, axis)) * rect->getHalfHeight();
    }
}// Physics


