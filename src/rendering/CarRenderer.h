//
// Created by simon on 4/11/26.
//

#ifndef CARRENDERER_H
#define CARRENDERER_H

#include <raylib.h>
#include "../physics/Rigidbody.h"

namespace  Rendering {
    class CarRenderer {
    public:
        void draw(const Physics::State& state);
    };
}

#endif //CARRENDERER_H
