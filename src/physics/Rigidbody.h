//
// Created by simon on 4/11/26.
//

#ifndef RIGIDBODY_H
#define RIGIDBODY_H
#include <memory>
#include <raylib.h>
#include "raymath.h"
#include "../math/raylib_vector2_operators.h"

#include "CollisionShapes/CollisionShape.h"

namespace Physics {

/// @brief Holds the current physical state of a rigid body.
struct State {
    Vector2 position {0, 0}; ///< Positon in world space
    Vector2 velocity {0, 0}; ///< Velocity in world space
    Vector2 acceleration {0, 0}; ///< Acceleration in world space
    float rotation {0.f}; ///< Angle in radians
    float angularVel {0.f}; ///< Change in rotation per second in radians per second
    float angularAccel {0.f}; ///< Change in angular velocity per second in radians per second squared
};

/// @brief A simulated rigid body that integrates forces over time.
class Rigidbody {
public:
    explicit Rigidbody(float mass, bool isKinematic = true) :
    m_mass {mass},
    m_momentOfInertia {},
    m_isKinematic {isKinematic}
    {};

    /// Apply a force to the point specified on the RigidBody, this point is a point in the world coordinate system
    void applyForce(Vector2 force, Vector2 point);

    /// Apply a force directly to the center of the RigidBody
    void applyForceToCenter(Vector2 force);

    /// Apply an impulse (sudden change in velocity) to a specified point on the RigidBody in world coordinate system.
    void applyLinearImpulse(Vector2 linearImpulse, Vector2 point);

    /// Apply a torque to RigidBody, which rotates the RigidBody
    void applyTorque(float torque);

    /// Apply an impulse to the rotation, updating the angular velocity directly
    void applyAngularImpulse(float angularImpulse);


    /// @brief Advances the simulation by one timestep.
    ///
    /// Integrates accumulated forces and torques into acceleration,
    /// velocity, and position using semi-implicit Euler integration.
    /// Clears all force and torque accumulators after integration.
    ///
    /// @param dt Delta time in seconds. Should be a fixed timestep for stable simulation
    void step(float dt);

    /// Gets the velocity of RigidBody at a certain point in world coordinates
    Vector2 getLinearVelocityFromWorldPoint(Vector2 worldPoint) const;

    /// Gets the angular velocity of RigidBody at a certain point in world coordinates
    Vector2 getAngularVelocityFromWorldPoint(Vector2 worldPoint) const;

    /// Gets world vector from local vector
    Vector2 getWorldVector(Vector2 localVector) const;

    /// Gets local vector from world vector
    Vector2 getLocalVector(Vector2 worldVector) const;

    /// Gets local coordinate from world coordinate
    Vector2 getLocalPoint(Vector2 worldPoint) const;

    /// Gets world coordinate from local coordinate
    Vector2 getWorldPoint(Vector2 localPoint) const;

    [[nodiscard]] const State& getState() const { return m_state; }
    State& getStateMutable() { return m_state; } /// Getter for mutating state
    float getMass()             const { return m_mass; }
    float getMomentOfInertia()  const { return m_momentOfInertia; }
    bool isStatic() const { return !m_isKinematic; }
    [[nodiscard]] const CollisionShape* getShape() const { return m_shape.get(); }
    void setCollisionShape(std::unique_ptr<CollisionShape> shape);
    void setPosition(Vector2 position) { m_state.position = position; }
    void setRotation(float rotation) { m_state.rotation = rotation; }
    void setVelocity(Vector2 velocity) {m_state.velocity = velocity;}

private:
    State m_state; ///< Current kinematic state
    float m_mass {}; ///< Mass in kilograms
    Vector2 m_centerOfMass {0,0}; ///< Position of center of mass relative to the center
    float m_momentOfInertia {}; ///< Moment of inertia in kilogram metre squared
    Vector2 m_forceAccum {}; ///< Accumulated forces this tick in Newtons
    float m_torqueAccum {}; ///< Accumulated torque this tick in Newton-metres

    std::unique_ptr<CollisionShape> m_shape {nullptr};

    bool m_isKinematic {true}; ///< Boolean for whether the rigidbody can move
};

} // Physics

#endif //RIGIDBODY_H
