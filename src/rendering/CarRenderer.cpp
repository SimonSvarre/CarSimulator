//
// Created by simon on 4/11/26.
//

#include "CarRenderer.h"

#include <iostream>


namespace  Rendering {
    void CarRenderer::draw(const Physics::State &state, std::array<Simulation::Wheel, 4> wheels) {
        // Body
        DrawRectanglePro(
            { state.position.x, state.position.y, m_bodyWidth, m_bodyHeight },
            { m_bodyWidth/2.0f, m_bodyHeight/2.0f },
            state.rotation * RAD2DEG + 90.0f,
            DARKGRAY
        );

        // Direction indicator so you can see which way it's facing
        Vector2 front {
            state.position.x + cosf(state.rotation + PI/2.f) * 25.f,
            state.position.y + sinf(state.rotation + PI/2.f) * 25.f
        };
        DrawLineV(state.position, front, RED);

        // Wheels
        for (auto& wheel : wheels)
        {
            Vector2 pos {Vector2Rotate(wheel.getLocalPosition(), state.rotation) + state.position};
            float rotation {wheel.getSteeringAngle() + state.rotation };
            std::cout << RAD2DEG*wheel.getSteeringAngle() << std::endl;
            DrawRectanglePro(
            { pos.x, pos.y, m_wheelHeight, m_wheelWidth },
            { m_wheelHeight/2.0f, m_wheelWidth/2.0f },
            rotation * RAD2DEG + 90.0f,
            BLACK
            );
        }
    }
}
