//
// Created by simon on 4/27/26.
//

#include "World.h"

namespace World
{
    void World::draw() const
    {
        for (int i = 0; i < 4; i++)
        {
            const Simulation::Rectangle& rect = m_border[i];
            const Rendering::RectangleRenderer& rectRender {m_borderRenders[i]};
            rectRender.draw(rect.getPhysicsState());
        }
    }
}
