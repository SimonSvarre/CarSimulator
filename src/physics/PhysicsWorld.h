//
// Created by simon on 4/11/26.
//

#ifndef PHYSICSWORLD_H
#define PHYSICSWORLD_H

#include <algorithm>
#include <vector>

#include "Rigidbody.h"
#include "surface/Surface.h"

namespace Physics {

    /// Owns all physic bodies, steps them and resolves collision.
class PhysicsWorld {
public:
    void addRigidbody(Rigidbody* rigidbody) {
        m_rigidbodies.emplace_back(rigidbody);
    }
    void removeRigidbody(Rigidbody* rigidbody) {
        m_rigidbodies.erase(
        std::remove(m_rigidbodies.begin(), m_rigidbodies.end(), rigidbody),
        m_rigidbodies.end()
        );
    }
    void addSurface(Surface* surface) {
        m_surfaces.emplace_back(surface);
    }
    void removeSurface(Surface* surface) {
        m_surfaces.erase(
        std::remove(m_surfaces.begin(), m_surfaces.end(), surface),
        m_surfaces.end()
        );
    }
    void step(float dT);

private:
    std::vector<Rigidbody*> m_rigidbodies {};
    std::vector<Surface*>   m_surfaces;

    void applySurfaceFriction();
};

} // Physics

#endif //PHYSICSWORLD_H
