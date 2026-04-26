//
// Created by simon on 4/11/26.
//

#ifndef CARRENDERER_H
#define CARRENDERER_H

#include <raylib.h>
#include "../physics/Rigidbody.h"
#include "../simulation/car/Wheel.h"
#include <array>

namespace  Rendering {
    class CarRenderer {
    public:
        void draw(const Physics::State& state, std::array<Simulation::Wheel, 4> wheels);

    private:
        float m_bodyWidth {40.0f};
        float m_bodyHeight {20.0f};
        float m_wheelWidth {4.0f};
        float m_wheelHeight {8.0f};

    };

}

#endif //CARRENDERER_H
