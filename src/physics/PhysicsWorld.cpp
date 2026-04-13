//
// Created by simon on 4/11/26.
//

#include "PhysicsWorld.h"

#include <iostream>

#include "Collision/CollisionDetector.h"
#include "Collision/CollisionResolver.h"

namespace Physics {
    void PhysicsWorld::step(float dT) {
        applySurfaceFriction();

        for (const auto& rigidbody : m_rigidbodies) {
            rigidbody->step(dT);
        }
        // Broad + narrow phase + resolution
        for (size_t i = 0; i < m_rigidbodies.size(); i++) {
            for (size_t j = i + 1; j < m_rigidbodies.size(); j++) {
                Rigidbody* a = m_rigidbodies[i];
                Rigidbody* b = m_rigidbodies[j];

                if (!a->getShape() || !b->getShape())
                    continue;
                if (!CollisionDetector::aabbOverlap(
                    a->getShape()->getAABB(),
                    b->getShape()->getAABB()))
                    continue;

                CollisionManifold manifold = CollisionDetector::test(
                    a->getShape(),
                    b->getShape()
                );

                if (manifold.hasCollision)
                    CollisionResolver::resolve(a, b, manifold);
            }
        }
    }

    // TODO: It should probably be made into both static and dynamic seperatly so static is first called after integration
    // Also right now it only uses the surface friction, not rigidbody.
    void PhysicsWorld::applySurfaceFriction() {
        for (Rigidbody* body : m_rigidbodies) {
            if (body->isStatic()) continue;

            // Find which surface this body is currently on
            const Material* material { nullptr };
            for (const Surface* surface : m_surfaces) {
                if (surface->contains(body->getState().position)) {
                    material = &surface->getMaterial();
                    break;
                }
            }

            // Apply drag/friction based on surface material
            if (material) {
                body->applyForceToCenter({
                    -body->getState().velocity.x * material->dynamicFriction * body->getMass(),
                    -body->getState().velocity.y * material->dynamicFriction * body->getMass()
                });

                // Angular friction — opposes angular velocity
                body->applyTorque(-body->getState().angularVel * material->dynamicFriction * 250.0f);
            }
        }
    }
} // Physics