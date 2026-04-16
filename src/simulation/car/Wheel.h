//
// Created by simon on 4/11/26.
//

#ifndef WHEEL_H
#define WHEEL_H
#include <raylib.h>
#include "raymath.h"
#include "../../math/raylib_vector2_operators.h"

#include "../../physics/Rigidbody.h"
#include "../../physics/PhysicsMath.h"
#include "Tire.h"

namespace Simulation {
    class Wheel {
    public:
        void setPosition(Vector2 localPosition) {m_localPosition = localPosition;};
        void setDrive(const bool drive) {m_drive = drive;}
        void setSteerable(const bool steerable) {m_isSteerable = steerable;}
        bool isDriven() const {return m_drive;}
        bool isSteerable() const {return m_isSteerable;}
        void setSteerAngle(const float steerAngle) {m_steerAngle = steerAngle;}
        Vector2 getTractionForce(float throttle, float engineForce) const;
        const float pacejkaLateralForceMag(float Fz, float slipAngle) const;
        /// Pacejka formula for lateral force from http://www-cdr.stanford.edu/dynamic/bywire/tires.pdf
        Vector2 getLateralForce(const Physics::Rigidbody& chassis, float Fz) const;
        Vector2 getRollingResistance() const;
        Vector2 getBrakeForce() const;

        Vector2 getLocalPosition() const {return m_localPosition;};

    private:
        TireCoefficients m_tire {defaultTire};
        bool m_drive {false}; ///< Is this wheel driven by the engine
        bool m_isSteerable {false}; ///< Can the wheel be turned
        Vector2 m_localPosition {}; ///< Position relative to car center
        float m_steerAngle {}; ///< Steering angle in radians where 0 is pointing in same direction as car chassis
        float m_radius {0.0f}; ///< Radius of the wheel in meters
        float m_camberAngle {0.0f}; ///< Camber angle in degrees
        float m_angle {0.0f}; ///< Current rotation angle of wheel in radians
        float m_angularVelocity {0.0f}; ///< Current angular velocity of wheel rotation in radians per second
    };
}

#endif //WHEEL_H
