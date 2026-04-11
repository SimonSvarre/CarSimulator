//
// Created by simon on 4/11/26.
//

#include "PhysicsWorld.h"

namespace Physics {
    void PhysicsWorld::step(float dT) {
        for (const auto& rigidbody : m_rigidbodies) {
            rigidbody->step(dT);
        }
    }
} // Physics