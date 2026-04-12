//
// Created by simon on 4/11/26.
//

#include "Rigidbody.h"

#include "PhysicsMath.h"
#include "CollisionShapes/CollisionShapeCircle.h"
#include "CollisionShapes/CollisionShapeRectangle.h"

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
        m_state.velocity += linearImpulse / m_mass;

        Vector2 offset = getLocalPoint(point) - m_centerOfMass;
        m_state.angularVel += cross2D(offset, linearImpulse) / m_momentOfInertia;
    }

    void Rigidbody::applyTorque(float torque) {
        m_torqueAccum += torque;
    }

    void Rigidbody::applyAngularImpulse(float angularImpulse) {
        // Directly modify angular velocity — no dt involved
        m_state.angularVel += angularImpulse / m_momentOfInertia;
    }

    void Rigidbody::step(const float dt) {
        if (!m_isKinematic) {
            // Update shape rotation
            m_shape->setRotation(m_state.rotation);
            m_shape->setCenter(m_state.position);
            return;
        }

        // Linear — integrate force into velocity, velocity into position
        m_state.velocity += (m_forceAccum / m_mass) * dt;

        m_state.position += m_state.velocity * dt;

        // Angular — integrate torque into angular velocity, angular velocity into rotation
        m_state.angularVel  += (m_torqueAccum / m_mass) * dt;
        m_state.rotation    += m_state.angularVel * dt;

        // Clear accumulators for next tick
        m_forceAccum   = {0.f, 0.f};
        m_torqueAccum  = 0.f;

        // Update shape rotation
        m_shape->setRotation(m_state.rotation);
        m_shape->setCenter(m_state.position);
    }

    Vector2 Rigidbody::getLinearVelocityFromWorldPoint(Vector2 worldPoint) const {
        Vector2 offset {getLocalPoint(worldPoint)};
        return {
            m_state.velocity.x - m_state.angularVel * offset.y,
            m_state.velocity.y + m_state.angularVel * offset.x
        };
    }

    Vector2 Rigidbody::getAngularVelocityFromWorldPoint(Vector2 worldPoint) const {
        Vector2 offset {getLocalPoint(worldPoint)};
        return {
            -m_state.angularVel * offset.y,
             m_state.angularVel * offset.x
        };

    }

    Vector2 Rigidbody::getWorldVector(Vector2 localVector) const {
        return {
            localVector.x * cosf(m_state.rotation) - localVector.y * sinf(m_state.rotation),
            localVector.x * sinf(m_state.rotation) + localVector.y * cosf(m_state.rotation)
        };
    }

    Vector2 Rigidbody::getLocalVector(Vector2 worldVector) const {
        return {
            worldVector.x * cosf(m_state.rotation) + worldVector.y * sinf(m_state.rotation),
           -worldVector.x * sinf(m_state.rotation) + worldVector.y * cosf(m_state.rotation)
       };
    }

    Vector2 Rigidbody::getLocalPoint(Vector2 worldPoint) const {
        return getLocalVector(worldPoint - m_state.position);
    }

    Vector2 Rigidbody::getWorldPoint(Vector2 localPoint) const {
        Vector2 rotated { getWorldVector(localPoint) };
        return {rotated + m_state.position};
    }

    void Rigidbody::setCollisionShape(std::unique_ptr<CollisionShape> shape) {
        m_shape = std::move(shape);

        // Recalculate moment of inertia based on shape
        if (m_shape->getType() == ShapeType::Rectangle) {
            const auto* rect = dynamic_cast<const CollisionShapeRectangle*>(m_shape.get());
            float w { rect->getHalfWidth()  * 2.f };
            float h { rect->getHalfHeight() * 2.f };
            m_momentOfInertia = MomentOfInertia::rectangle(m_mass, w, h);
        }
        else if (m_shape->getType() == ShapeType::Circle) {
            const auto* circle = dynamic_cast<const CollisionShapeCircle*>(m_shape.get());
            m_momentOfInertia = MomentOfInertia::solidCircle(m_mass, circle->getRadius());
        }
    }
} // Physics