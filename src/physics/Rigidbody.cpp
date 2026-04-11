//
// Created by simon on 4/11/26.
//

#include "Rigidbody.h"

namespace Physics {
    void Rigidbody::step(float dt) {
        // Linear — integrate force into velocity, velocity into position
        m_state.velocity.x += (m_forceAccum.x / m_mass) * dt;
        m_state.velocity.y += (m_forceAccum.y / m_mass) * dt;

        m_state.position.x += m_state.velocity.x * dt;
        m_state.position.y += m_state.velocity.y * dt;

        // Angular — integrate torque into angular velocity, angular velocity into rotation
        m_state.angularVel  += (m_torqueAccum / m_mass) * dt;
        m_state.rotation    += m_state.angularVel * dt;

        // Clear accumulators for next tick
        m_forceAccum   = {0.f, 0.f};
        m_torqueAccum  = 0.f;
    }
} // Physics