//
// Created by simon on 4/12/26.
//

#include "CollisionResolver.h"
#include "../PhysicsMath.h"

namespace Physics {
    void CollisionResolver::resolve(Rigidbody *a, Rigidbody *b, const CollisionManifold &manifold) {
        // --- Step 1: Positional correction ---
    // Push bodies apart so they are no longer penetrating
    const float correction { manifold.depth / (a->getMass() + b->getMass()) * 0.8f };
    a->getStateMutable().position -= manifold.normal * (correction * b->getMass());
    b->getStateMutable().position += manifold.normal * (correction * a->getMass());

    // --- Step 2: Impulse resolution ---
    // Velocity of each body at the contact point
    Vector2 velA { a->getLinearVelocityFromWorldPoint(manifold.contactPoint) };
    Vector2 velB { b->getLinearVelocityFromWorldPoint(manifold.contactPoint) };

    // Relative velocity along the normal
    Vector2 relVel { velB.x - velA.x, velB.y - velA.y };
    float   relVelAlongNormal { Vector2DotProduct(relVel, manifold.normal) };

    // Bodies are already separating — no impulse needed
    if (relVelAlongNormal > 0.f)
        return;

    // Vectors from center of mass to contact point
    Vector2 rA {
        manifold.contactPoint.x - a->getState().position.x,
        manifold.contactPoint.y - a->getState().position.y
    };
    Vector2 rB {
        manifold.contactPoint.x - b->getState().position.x,
        manifold.contactPoint.y - b->getState().position.y
    };

    // Cross products for rotational contribution
    float rACrossN { cross2D(rA, manifold.normal) };
    float rBCrossN { cross2D(rB, manifold.normal) };

    // Effective inverse mass — accounts for both linear and rotational inertia
    float invMassSum {
        (1.f / a->getMass()) + (1.f / b->getMass())
        + (rACrossN * rACrossN) / a->getMomentOfInertia()
        + (rBCrossN * rBCrossN) / b->getMomentOfInertia()
    };

    // Impulse scalar
    float j { -(1.f + RESTITUTION) * relVelAlongNormal / invMassSum };

    Vector2 impulse { manifold.normal.x * j, manifold.normal.y * j };

    // Apply impulse — equal and opposite to each body
    a->applyLinearImpulse({ -impulse.x, -impulse.y }, manifold.contactPoint);
    b->applyLinearImpulse({  impulse.x,  impulse.y }, manifold.contactPoint);
    }
} // Physics