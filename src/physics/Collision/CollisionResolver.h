//
// Created by simon on 4/12/26.
//

#ifndef COLLISIONRESOLVER_H
#define COLLISIONRESOLVER_H
#include "CollisionManifold.h"
#include "../Rigidbody.h"

namespace Physics {

    class CollisionResolver {
    public:
        static void resolve(Rigidbody* a, Rigidbody* b, const CollisionManifold& manifold);

    private:
        static constexpr float RESTITUTION = 0.4f;  // bounciness 0-1
    };

} // namespace Physics
#endif
