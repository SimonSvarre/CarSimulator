cmake_minimum_required(VERSION 3.31)
project(CarSimulator)

set(CMAKE_TOOLCHAIN_FILE "/opt/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

add_executable(CarSimulator src/main.cpp
        src/physics/Rigidbody.cpp
        src/physics/Rigidbody.h
        src/physics/PhysicsMath.h
        src/rendering/CarRenderer.cpp
        src/rendering/CarRenderer.h
        src/simulation/car/Car.cpp
        src/simulation/car/Car.h
        src/simulation/car/Wheel.cpp
        src/simulation/car/Wheel.h
        src/physics/PhysicsWorld.cpp
        src/physics/PhysicsWorld.h
        src/physics/CollisionShapes/CollisionShape.h
        src/physics/CollisionShapes/CollisionShapeCircle.h
        src/physics/CollisionShapes/CollisionShapeCircle.cpp
        src/physics/CollisionShapes/CollisionShapeRectangle.cpp
        src/physics/CollisionShapes/CollisionShapeRectangle.h
        src/physics/Collision/CollisionManifold.h
        src/physics/Collision/CollisionDetector.cpp
        src/physics/Collision/CollisionDetector.h
        src/physics/Collision/CollisionResolver.cpp
        src/physics/Collision/CollisionResolver.h
        src/rendering/RectangleRenderer.cpp
        src/rendering/RectangleRenderer.h
        src/simulation/shapes/Rectangle.cpp
        src/simulation/shapes/Rectangle.h
        src/rendering/DebugDraw.cpp
        src/rendering/DebugDraw.h
        src/physics/surface/Surface.h
        src/physics/Material.h
        src/physics/surface/Surface.cpp)

find_package(raylib CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

# Link everything raylib depends on explicitly
target_link_libraries(CarSimulator PRIVATE
        raylib
        glfw
        pthread
        dl
        m
        X11
        Xrandr
        Xinerama
        Xcursor
        GL
)