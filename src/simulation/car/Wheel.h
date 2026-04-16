//
// Created by simon on 4/11/26.
//

#ifndef WHEEL_H
#define WHEEL_H
#include <raylib.h>
#include "raymath.h"
#include "../../math/raylib_vector2_operators.h"

#include "../../physics/Rigidbody.h"

namespace Simulation {
    class Wheel {
    public:
        void setDrive(const bool drive) {m_drive = drive;}
        bool isDriven() const {return m_drive;}
        Vector2 getTractionForce(float throttle, float engineForce) const;
        Vector2 getLateralForce(const Physics::Rigidbody& chassis) const;
        Vector2 getRollingResistance() const;
        Vector2 getBrakeForce() const;

        Vector2 getLocalPosition() const {return m_localPosition;};

    private:
        bool m_drive {false}; ///< Is this wheel driven by the engine
        bool m_isSteerable {false}; ///< Can the wheel be turned
        Vector2 m_localPosition {}; ///< Position relative to car center
        float m_steerAngle {}; ///< Steering angle in radians where 0 is pointing in same direction as car chassis
        float m_radius {0.0f}; ///< Radius of the wheel in meters
        float m_angle {0.0f}; ///< Current rotation angle of wheel in radians
        float m_angularVelocity {0.0f}; ///< Current angular velocity of wheel rotation in radians per second
    };
}

#endif //WHEEL_H
