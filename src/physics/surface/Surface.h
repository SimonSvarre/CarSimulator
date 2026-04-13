//
// Created by simon on 4/13/26.
//

#ifndef SURFACE_H
#define SURFACE_H

#include <memory>
#include "../CollisionShapes/CollisionShape.h"
#include "..//Material.h"

namespace Physics {

class Surface {
public:
    Surface(const Material material, std::unique_ptr<CollisionShape> shape) : m_shape(std::move(shape)), m_material(material) {}
    [[nodiscard]] const CollisionShape* getShape() const { return m_shape.get(); }
    CollisionShape* getShapeMutable() {return m_shape.get();}
    const Material& getMaterial() const { return m_material; }

    /// Returns true if the given world point is inside this surface
    bool contains(Vector2 point) const;
private:
    std::unique_ptr<CollisionShape> m_shape {nullptr};
    Material m_material;
};

}

#endif //SURFACE_H