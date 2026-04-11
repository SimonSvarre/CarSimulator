//
// Created by simon on 4/11/26.
//

#ifndef CAR_H
#define CAR_H
#include <array>
#include <raylib.h>
#include <raymath.h>

#include "../../physics/Rigidbody.h"
#include "Wheel.h"

namespace Simulation {


    class Car {
    public:
        explicit Car(float mass): m_body{mass} {
            // Set rear-wheel drive by default
            m_wheels[2].setDrive(true);
            m_wheels[3].setDrive(true);
        };
        [[nodiscard]] const Physics::State& getPhysicsState() const {return m_body.getState();};
        Physics::Rigidbody* getRigidbody() { return &m_body; }

        void accelerate(float amount) { // These are only for testing
            // amount is -1.0 to 1.0, negative for reverse
            float engineForce = amount * m_engineForce;

            Vector2 force {0, 1};
            force = m_body.getWorldVector(force*engineForce);

            m_body.applyForceToCenter(force);
        }

        void turn(float amount) {
            // amount is -1.0 to 1.0, negative for left
            m_body.applyTorque(amount * m_turnTorque);
        }
    private:
        Physics::Rigidbody m_body;
        std::array<Wheel, 4> m_wheels {}; ///< Array with wheels of the car where lf = index 0, rf = 1, lr = 2, rr = 3

        float m_engineForce = 50000.f;   // Newtons
        float m_turnTorque  = 1500.f;   // Newton-metres
        float m_axleOffset  = 20.f;     // pixels from center to rear axle
    };
}

#endif //CAR_H
