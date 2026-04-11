//
// Created by simon on 4/11/26.
//

#ifndef CAR_H
#define CAR_H
#include <array>

#include "../../physics/Rigidbody.h"
#include "Wheel.h"

namespace Simulation {


    class Car {
    public:
        explicit Car(float mass): body{mass} {
            // Set rear-wheel drive by default
            wheels[2].setDrive(true);
            wheels[3].setDrive(true);
        };
        [[nodiscard]] const Physics::State& getPhysicsState() const {return body.getState();};
    private:
        Physics::Rigidbody body;
        std::array<Wheel, 4> wheels {}; ///< Array with wheels of the car where lf = index 0, rf = 1, lr = 2, rr = 3
    };
}

#endif //CAR_H
