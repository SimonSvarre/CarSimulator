//
// Created by simon on 4/11/26.
//

#ifndef CAR_H
#define CAR_H
#include <array>
#include <raylib.h>
#include <raymath.h>
#include "../../math/raylib_vector2_operators.h"

#include "../../physics/Rigidbody.h"
#include "Wheel.h"


namespace Simulation {


    class Car {
    public:
        explicit Car(float mass, float length, float width): m_body{mass} {
            // Set rear-wheel drive by default
            m_wheels[2].setDrive(true);
            m_wheels[3].setDrive(true);

            m_wheels[0].setSteerable(true);
            m_wheels[1].setSteerable(true);

            m_wheels[0].setPosition({width / 2, length / 2});
            m_wheels[1].setPosition({-width / 2, length / 2});
            m_wheels[2].setPosition({width / 2, -length / 2});
            m_wheels[3].setPosition({-width / 2, -length / 2});
        };
        [[nodiscard]] const Physics::State& getPhysicsState() const {return m_body.getState();};
        Physics::Rigidbody* getRigidbody() { return &m_body; }

        void step(float dt);
        void setThrottle(float throttle) {m_throttle = throttle;};
        void setSteeringAngle(float steeringAngle);;
        std::array<Vector2, 4> getLateralForces();
        std::array<Wheel, 4> getWheels() {return m_wheels;};

        void accelerate(float amount) { // These are only for testing
            // amount is -1.0 to 1.0, negative for reverse
            float engineForce = amount * m_engineForce;

            Vector2 force {0, 1};
            force = m_body.getWorldVector(Vector2Scale(force, engineForce));

            m_body.applyForceToCenter(force);
        }

        void turn(float amount) {
            // amount is -1.0 to 1.0, negative for left
            m_body.applyTorque(amount * m_turnTorque);
        }
    private:
        Physics::Rigidbody m_body;
        std::array<Wheel, 4> m_wheels {}; ///< Array with wheels of the car where lf = index 0, rf = 1, lr = 2, rr = 3

        float m_engineForce = 50000.f;   /// Newtons
        float m_turnTorque  = 1500.f;   /// Newton-metres
        float m_axleOffset  = 20.f;     /// pixels from center to rear axle

        float m_maxSteeringAngle {35.0f}; /// Max angle car can steer wheels in degrees

        float m_throttle = 0.0f; /// How much throttle is being applied from 0 to 1.
    };
}

#endif //CAR_H
