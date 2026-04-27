//
// Created by simon on 4/12/26.
//

#ifndef RECTANGLERENDERER_H
#define RECTANGLERENDERER_H
#include <raylib.h>
#include "../physics/PhysicsWorld.h"
#include "../simulation/shapes/Rectangle.h"

namespace Rendering {
    class RectangleRenderer {
    public:
        RectangleRenderer(float width, float height, Color color)
            : m_width{width}, m_height{height}, m_color{color} {}
        RectangleRenderer(const Simulation::Rectangle& rectangle, Color color)
            : m_width{rectangle.getExtent().x}, m_height{rectangle.getExtent().y}, m_color{color} {}

        void draw(const Physics::State& state) const;

    private:
        float m_width;
        float m_height;
        Color m_color;
    };
} // Rendering

#endif //RECTANGLERENDERER_H
