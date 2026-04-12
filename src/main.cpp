#include <iostream>
#include "raylib.h"
#include "physics/PhysicsWorld.h"
#include "physics/CollisionShapes/CollisionShapeRectangle.h"
#include "rendering/CarRenderer.h"
#include "simulation/car/Car.h"

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    constexpr int SCREENWIDTH = 800;
    constexpr int SCREENHEIGHT = 450;

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Car Simulator");

    SetTargetFPS(60);

    Physics::PhysicsWorld physicsWorld {};

    Simulation::Car car {1000};
    physicsWorld.addRigidbody(car.getRigidbody());
    car.getRigidbody()->setCollisionShape(std::make_unique<Physics::CollisionShapeRectangle>(20.0f, 40.0f));
    Rendering::CarRenderer carRenderer {};


    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
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
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
