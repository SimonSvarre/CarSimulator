//
// Created by simon on 4/12/26.
//

#ifndef DEBUGDRAW_H
#define DEBUGDRAW_H

#include <raylib.h>
#include "../physics/Rigidbody.h"

namespace Rendering {

    class DebugDraw {
    public:
        bool enabled {true};

        void drawAABB(const Physics::Rigidbody* body) const;
        void drawVelocity(const Physics::State& state) const;
        void drawContactPoint(Vector2 point) const;
    };

} // namespace Rendering

#endif //DEBUGDRAW_H
