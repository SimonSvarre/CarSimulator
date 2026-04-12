//
// Created by simon on 4/12/26.
//

#include "CollisionResolver.h"
#include "../PhysicsMath.h"

namespace Physics {
    void CollisionResolver::resolve(Rigidbody* a, Rigidbody* b, const CollisionManifold& manifold) {
        float invMassA { a->isStatic() ? 0.f : 1.f / a->getMass() };
        float invMassB { b->isStatic() ? 0.f : 1.f / b->getMass() };

        float invMoIA  { a->isStatic() ? 0.f : 1.f / a->getMomentOfInertia() };
        float invMoIB  { b->isStatic() ? 0.f : 1.f / b->getMomentOfInertia() };

        // Positional correction
        const float correction { manifold.depth / (invMassA + invMassB) * 0.8f };
        if (!a->isStatic()) a->setPosition(a->getState().position - manifold.normal * (correction * invMassA));
        if (!b->isStatic()) b->setPosition(b->getState().position + manifold.normal * (correction * invMassB));

        // Relative velocity
        Vector2 velA { a->getLinearVelocityFromWorldPoint(manifold.contactPoint) };
        Vector2 velB { b->getLinearVelocityFromWorldPoint(manifold.contactPoint) };
        Vector2 relVel { velB.x - velA.x, velB.y - velA.y };
        float relVelAlongNormal { Vector2DotProduct(relVel, manifold.normal) };

        if (relVelAlongNormal > 0.f) return;

        Vector2 rA { manifold.contactPoint.x - a->getState().position.x,
                     manifold.contactPoint.y - a->getState().position.y };
        Vector2 rB { manifold.contactPoint.x - b->getState().position.x,
                     manifold.contactPoint.y - b->getState().position.y };

        float rACrossN { cross2D(rA, manifold.normal) };
        float rBCrossN { cross2D(rB, manifold.normal) };

        float invMassSum {
            invMassA + invMassB
            + (rACrossN * rACrossN) * invMoIA
            + (rBCrossN * rBCrossN) * invMoIB
        };

        float j { -(1.f + RESTITUTION) * relVelAlongNormal / invMassSum };
        Vector2 impulse { manifold.normal.x * j, manifold.normal.y * j };

        if (!a->isStatic()) a->applyLinearImpulse({ -impulse.x, -impulse.y }, manifold.contactPoint);
        if (!b->isStatic()) b->applyLinearImpulse({  impulse.x,  impulse.y }, manifold.contactPoint);
    }
}