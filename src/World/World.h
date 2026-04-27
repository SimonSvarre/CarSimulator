//
// Created by simon on 4/27/26.
//

#ifndef CARSIMULATOR_WORLD_H
#define CARSIMULATOR_WORLD_H
#include <array>
#include "../simulation/shapes/Rectangle.h"
#include "../rendering/RectangleRenderer.h"

namespace World
{
    class World {
    public:
        World(Physics::PhysicsWorld* physicsWorld, Vector2 worldSize)
        : m_border{
            Simulation::Rectangle(worldSize.x, 10.0f, 10000, 0.0f, {worldSize.x/2.0f, 0.0f}, false),
            Simulation::Rectangle(worldSize.x, 10.0f, 10000, 90.0f, {0.0f, worldSize.y/2.0f}, false),
            Simulation::Rectangle(worldSize.x, 10.0f, 10000, 0.0f, {worldSize.x/2.0f, worldSize.y}, false),
            Simulation::Rectangle(worldSize.x, 10.0f, 10000, 90.0f, {worldSize.x, worldSize.y/2.0f}, false)
        },
        m_borderRenders{
            Rendering::RectangleRenderer(m_border[0], m_borderColor),
            Rendering::RectangleRenderer(m_border[1], m_borderColor),
            Rendering::RectangleRenderer(m_border[2], m_borderColor),
            Rendering::RectangleRenderer(m_border[3], m_borderColor)
        }
        {
            for (auto& rect : m_border)
            {
                physicsWorld->addRigidbody(rect.getRigidbody());
            }

        }

        void draw() const;
    private:
        bool m_renderBorders {true};
        Color m_borderColor {DARKBLUE};
        std::array<Simulation::Rectangle, 4> m_border;
        std::array<Rendering::RectangleRenderer, 4> m_borderRenders;
    };
}

#endif //CARSIMULATOR_WORLD_H
