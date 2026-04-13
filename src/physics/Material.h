//
// Created by simon on 4/13/26.
//

#ifndef MATERIAL_H
#define MATERIAL_H

namespace Physics {
    struct Material {
        float dynamicFriction; ///< The friction used when already moving. Usually a value from 0 to 1 where 0 is like ice.
        float staticFriction; ///< The friction used when object is stationary. Usually a value from 0 to 1 where 0 is like ice.
    };
}

#endif //MATERIAL_H
