//
// Created by simon on 4/11/26.
//

#include "Car.h"

namespace Simulation {
    void Car::step(float dt)
    {
        for (auto& wheel : m_wheels)
        {
            if (wheel.isDriven())
            {
                Vector2 wheelPos {m_body.getWorldPoint(wheel.getLocalPosition())};
                m_body.applyForce(wheel.getTractionForce(m_throttle, m_engineForce), wheelPos);
            }
        }
    }
}
