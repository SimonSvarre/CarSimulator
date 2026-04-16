//
// Created by simon on 4/12/26.
//

#include "DebugDraw.h"

namespace Rendering {

    void DebugDraw::drawAABB(const Physics::Rigidbody* body) const {
        if (!enabled) return;
        if (!body->getShape()) return;

        Physics::AABB aabb { body->getShape()->getAABB() };

        float width  { aabb.max.x - aabb.min.x };
        float height { aabb.max.y - aabb.min.y };

        DrawRectangleLinesEx(
            { aabb.min.x, aabb.min.y, width, height },
            1.f,
            GREEN
        );
    }

    void DebugDraw::drawVelocity(const Physics::State& state) const {
        if (!enabled) return;

        // Draw velocity as a line from the body center
        Vector2 velEnd {
            state.position.x + state.velocity.x,
            state.position.y + state.velocity.y
        };
        DrawLineV(state.position, velEnd, RED);
    }

    void DebugDraw::drawContactPoint(Vector2 point) const {
        if (!enabled) return;
        DrawCircleV(point, 4.f, YELLOW);
    }

    void DebugDraw::drawVector(Vector2 vector, Vector2 pos) const
    {
        DrawLineV(pos, pos + vector, BLUE);
    }
} // namespace Rendering