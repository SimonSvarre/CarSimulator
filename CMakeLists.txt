cmake_minimum_required(VERSION 3.16...3.28)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

project(CarSimulator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Avoid building unnecessary stuff
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.0
)

FetchContent_MakeAvailable(raylib)

add_executable(CarSimulator
        src/main.cpp
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
        src/physics/surface/Surface.cpp
        src/math/raylib_vector2_operators.h
        src/simulation/car/Tire.h
)

target_link_libraries(CarSimulator PRIVATE raylib)