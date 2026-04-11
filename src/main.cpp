#include <iostream>
#include "raylib.h"
#include "rendering/CarRenderer.h"
#include "simulation/car/Car.h"

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    constexpr int SCREENWIDTH = 800;
    constexpr int SCREENHEIGHT = 450;

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Car Simulator");

    SetTargetFPS(60);

    Simulation::Car car {1000};
    Rendering::CarRenderer carRenderer {};
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
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
