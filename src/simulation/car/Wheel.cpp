//
// Created by simon on 4/11/26.
//

#include "Wheel.h"



namespace Simulation {
    Vector2 Wheel::getTractionForce(float throttle, float engineForce) const
    {
        const Vector2 tractionDirection {Vector2Rotate(Vector2{0,1}, m_steerAngle)};
        Vector2 tractionForce = tractionDirection * throttle * engineForce; // This should obviously be made more complex at some point

        return tractionForce;
    }
}
