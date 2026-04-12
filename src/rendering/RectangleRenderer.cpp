//
// Created by simon on 4/12/26.
//

#include "RectangleRenderer.h"

#include <iostream>
#include <bits/ostream.tcc>

namespace Rendering {
    void RectangleRenderer::draw(const Physics::State &state) const {
        DrawRectanglePro({state.position.x, state.position.y, m_width, m_height},
            {m_width/2.0f, m_height/2.0f},
            state.rotation,
            m_color);
    }
} // Rendering