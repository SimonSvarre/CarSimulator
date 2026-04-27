//
// Created by simon on 4/12/26.
//

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "../../physics/PhysicsWorld.h"
#include "../../physics/CollisionShapes/CollisionShapeRectangle.h"

namespace Simulation {

class Rectangle {
public:
    ///
    /// @param width how wide it is
    /// @param height how tall it is
    /// @param mass mass in kg
    /// @param rotation rotation in degrees
    /// @param position the starting position
    /// @param isKinematic whether it can be moved by forces
    Rectangle(float width, float height, float mass, float rotation = 0.0f, Vector2 position = {0.0f,0.0f}, bool isKinematic = true) : m_body{mass, isKinematic} {
        m_body.setRotation(DEG2RAD*rotation);
        m_body.setPosition(position);
        m_body.setCollisionShape(std::make_unique<Physics::CollisionShapeRectangle>(width, height));
        m_extent = {width, height};
    }
    Physics::Rigidbody* getRigidbody() { return &m_body; }
    [[nodiscard]] const Physics::State& getPhysicsState() const {return m_body.getState();};
    Vector2 getExtent() const { return m_extent; };
private:
    Physics::Rigidbody m_body;
    Vector2 m_extent;
};

} // Simulation

#endif //RECTANGLE_H
