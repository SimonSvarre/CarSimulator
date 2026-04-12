//
// Created by simon on 4/12/26.
//

#ifndef COLLISIONMANIFOLD_H
#define COLLISIONMANIFOLD_H
#include <raylib.h>

namespace Physics {

    struct CollisionManifold {
        bool hasCollision {false};
        Vector2 normal {};   ///< direction to push A out of B
        float depth {}; ///< penetration depth
        Vector2 contactPoint {}; ///< world space contact point
    };

} // namespace Physics
#endif
