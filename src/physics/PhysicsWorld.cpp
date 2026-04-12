//
// Created by simon on 4/11/26.
//

#include "PhysicsWorld.h"

#include "Collision/CollisionDetector.h"
#include "Collision/CollisionResolver.h"

namespace Physics {
    void PhysicsWorld::step(float dT) {
        for (const auto& rigidbody : m_rigidbodies) {
            rigidbody->step(dT);
        }
        // Broad + narrow phase + resolution
        for (size_t i = 0; i < m_rigidbodies.size(); i++) {
            for (size_t j = i + 1; j < m_rigidbodies.size(); j++) {
                Rigidbody* a = m_rigidbodies[i];
                Rigidbody* b = m_rigidbodies[j];

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
} // Physics