//
// Created by simon on 4/11/26.
//

#include "CarRenderer.h"

namespace  Rendering {
    void CarRenderer::draw(const Physics::State &state) {
        // Body
        DrawRectanglePro(
            { state.position.x, state.position.y, 40.f, 20.f },
            { 20.f, 10.f },
            state.rotation * RAD2DEG,
            DARKGRAY
        );

        // Direction indicator so you can see which way it's facing
        Vector2 front {
            state.position.x + cosf(state.rotation) * 25.f,
            state.position.y + sinf(state.rotation) * 25.f
        };
        DrawLineV(state.position, front, RED);
    }
}
