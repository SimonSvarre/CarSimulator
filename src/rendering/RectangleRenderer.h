//
// Created by simon on 4/12/26.
//

#ifndef RECTANGLERENDERER_H
#define RECTANGLERENDERER_H
#include <raylib.h>
#include "../physics/PhysicsWorld.h"

namespace Rendering {
    class RectangleRenderer {
    public:
        RectangleRenderer(float width, float height, Color color)
            : m_width{width}, m_height{height}, m_color{color} {}

        void draw(const Physics::State& state) const;

    private:
        float m_width;
        float m_height;
        Color m_color;
    };
} // Rendering

#endif //RECTANGLERENDERER_H
