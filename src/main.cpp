#include <iostream>
#include "raylib.h"
#include "physics/PhysicsWorld.h"
#include "physics/CollisionShapes/CollisionShapeRectangle.h"
#include "rendering/CarRenderer.h"
#include "rendering/DebugDraw.h"
#include "rendering/RectangleRenderer.h"
#include "simulation/car/Car.h"
#include "simulation/shapes/Rectangle.h"

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    constexpr int SCREENWIDTH = 800;
    constexpr int SCREENHEIGHT = 450;

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Car Simulator");

    SetTargetFPS(60);

    Rendering::DebugDraw debugDraw;

    Physics::PhysicsWorld physicsWorld {};

    Simulation::Car car {1000};
    physicsWorld.addRigidbody(car.getRigidbody());
    car.getRigidbody()->setCollisionShape(std::make_unique<Physics::CollisionShapeRectangle>(20.0f, 40.0f));
    Rendering::CarRenderer carRenderer {};

    Simulation::Rectangle testKinematicBox {70.0f, 70.0f, 200.0f, 0.0f, {SCREENWIDTH/2.0f, SCREENHEIGHT/2.0f}};
    physicsWorld.addRigidbody(testKinematicBox.getRigidbody());
    Rendering::RectangleRenderer rectangleRenderer {70.0f, 70.0f, RED};
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_F)) debugDraw.enabled = !debugDraw.enabled;

        float deltaTime = GetFrameTime();

        if (IsKeyDown(KEY_W)) car.accelerate(1.f);
        if (IsKeyDown(KEY_S)) car.accelerate(-1.f);
        if (IsKeyDown(KEY_A)) car.turn(-1.f);
        if (IsKeyDown(KEY_D)) car.turn(1.f);

        physicsWorld.step(deltaTime);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        carRenderer.draw(car.getPhysicsState());
        rectangleRenderer.draw(testKinematicBox.getPhysicsState());

        debugDraw.drawAABB(car.getRigidbody());
        debugDraw.drawAABB(testKinematicBox.getRigidbody());
        debugDraw.drawVelocity(car.getPhysicsState());
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
