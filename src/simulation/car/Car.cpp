//
// Created by simon on 4/11/26.
//

#include "Car.h"

#include <iostream>

namespace Simulation {
    void Car::turnWheels(const float dt, std::array<Wheel, 4>::value_type& wheel) const
    {
        float currentAngle {wheel.getSteeringAngle()};
        float targetAngle {m_steeringAngle * DEG2RAD};
        wheel.setSteerAngle(Lerp(currentAngle, targetAngle, dt *m_steeringSpeed));
    }

    void Car::step(float dt)
    {
        for (auto& wheel : m_wheels)
        {

            if (wheel.isSteerable())
            {
                turnWheels(dt, wheel);
            }
        }

        for (auto& wheel : m_wheels)
        {
            Vector2 wheelWorldPos {m_body.getWorldPoint(wheel.getLocalPosition())};
            if (wheel.isDriven())
            {
                m_body.applyForce(m_body.getWorldVector(wheel.getTractionForce(m_throttle, m_engineForce)), wheelWorldPos);
                if (m_body.getWorldVector(wheel.getTractionForce(m_throttle, m_engineForce)).y < 0.0f)
                {
                    std::cout<< m_body.getWorldVector(wheel.getTractionForce(m_throttle, m_engineForce)).x << " " << m_body.getWorldVector(wheel.getTractionForce(m_throttle, m_engineForce)).y<< std::endl;
                }

            }
            Vector2 lateralForce {wheel.getLateralForce(m_body, Physics::GRAVITY * m_body.getMass() / m_wheels.size() / 1000.0f)};
            Vector2 worldLateralForce = m_body.getWorldVector(lateralForce);
            if (Vector2Length(lateralForce) > 0.0f)
            {
                //std::cout << worldLateralForce.x << ", " << worldLateralForce.y  << std::endl;
                Vector2 testLateralForce {wheel.getLateralForce(m_body, Physics::GRAVITY * m_body.getMass() / m_wheels.size())};
            }
            m_body.applyForce(worldLateralForce, wheelWorldPos);
        }
    }

    void Car::setSteeringAngle(float steeringAngle)
    {
        if (steeringAngle > m_maxSteeringAngle)
        {
            steeringAngle = m_maxSteeringAngle;
        }
        if (steeringAngle < -m_maxSteeringAngle)
        {
            steeringAngle = -m_maxSteeringAngle;
        }
        m_steeringAngle = steeringAngle;
    }

    std::array<Vector2, 4> Car::getLateralForces()
    {
        std::array<Vector2, 4> lateralForces{};

        for (std::size_t i = 0; i < m_wheels.size(); ++i)
        {
            lateralForces[i] = m_body.getWorldVector(m_wheels[i].getLateralForce(m_body, Physics::GRAVITY * m_body.getMass() / m_wheels.size()/100000.0f));
        }

        return lateralForces;
    }
}
