//
// Created by simon on 4/11/26.
//

#include "Wheel.h"

#include <iostream>


namespace Simulation {
    Vector2 Wheel::getTractionForce(float throttle, float engineForce) const
    {
        const Vector2 tractionDirection {Vector2Rotate(Vector2{0,1}, m_steerAngle)};
        Vector2 tractionForce = tractionDirection * throttle * engineForce; // This should obviously be made more complex at some point

        return tractionForce;
    }

    const float Wheel::pacejkaLateralForceMag(float Fz, float slipAngle) const
    {
        const float C {1.30f};
        const float D {m_tire.Fy.a1 * Fz*Fz + m_tire.Fy.a2 * Fz};
        const float BCD {m_tire.Fy.a3 * sin(m_tire.Fy.a4 * atan(m_tire.Fy.a5 * Fz))};
        const float B {BCD/(C*D)};
        const float E {m_tire.Fy.a6 * Fz*Fz + m_tire.Fy.a7 * Fz + m_tire.Fy.a8};

        // Camber angle factors
        const float Sh {m_tire.Fy.a9 * m_camberAngle};
        const float Sv {(m_tire.Fy.a10 * Fz*Fz + m_tire.Fy.a11 * Fz) * m_camberAngle};
        const float deltaB {-m_tire.Fy.a12 * abs(m_camberAngle) * B};

        // Lateral force
        const float alpha {slipAngle * RAD2DEG};
        const float phi {(1-E)*(alpha + Sh) + E/B * atan(B*(alpha + Sh))};
        const float Fy {D * sin(C * atan(B * phi)) + Sv};
        return Fy;
    }

    Vector2 Wheel::getLateralForce(const Physics::Rigidbody& chassis, float Fz) const
    {
        // World heading of this wheel (chassis rotation + steer angle)
        Vector2 wheelHeading { Vector2Rotate(Vector2One(),chassis.getState().rotation + m_steerAngle)};

        // Velocity of the chassis at this wheel's world position
        Vector2 wheelWorldPos { chassis.getWorldPoint(m_localPosition) };
        Vector2 wheelVelocity { chassis.getLinearVelocityFromWorldPoint(wheelWorldPos) };

        float speed { Vector2Length(wheelVelocity) };
        if (speed < 0.1f) return {0.f, 0.f};  // no meaningful slip at rest

        // Angle between wheel heading and actual velocity direction
        float slipAngle { Vector2Angle(chassis.getState().velocity, wheelHeading) };

        const float Fy = pacejkaLateralForceMag(Fz, slipAngle);

        return {
            -sinf(m_steerAngle) * Fy,
            cosf(m_steerAngle) * Fy,
        };
    }
}
