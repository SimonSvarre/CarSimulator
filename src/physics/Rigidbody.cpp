//
// Created by simon on 4/11/26.
//

#include "Rigidbody.h"

#include "PhysicsMath.h"

namespace Physics {
    void Rigidbody::applyForce(const Vector2 force, const Vector2 point) {
        m_forceAccum += force;

        const Vector2 offset = getLocalPoint(point) - m_centerOfMass;
        m_torqueAccum += cross2D(offset, force);
    }

    void Rigidbody::applyForceToCenter(Vector2 force) {
        m_forceAccum += force;
    }

    void Rigidbody::applyLinearImpulse(Vector2 linearImpulse, Vector2 point) {
        // Directly modify linear velocity — no dt involved
        m_state.velocity.x += linearImpulse.x / m_mass;
        m_state.velocity.y += linearImpulse.y / m_mass;

        // Impulse at a point also produces an angular impulse
        Vector2 offset = {
            point.x - m_state.position.x,
            point.y - m_state.position.y
        };
        m_state.angularVel += cross2D(offset, linearImpulse) / m_momentOfInertia;
    }

    void Rigidbody::applyTorque(float torque) {
        // Accumulate — gets integrated in step()
        m_torqueAccum += torque;
    }

    void Rigidbody::applyAngularImpulse(float angularImpulse) {
        // Directly modify angular velocity — no dt involved
        m_state.angularVel += angularImpulse / m_momentOfInertia;
    }

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