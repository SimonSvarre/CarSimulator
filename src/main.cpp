#include <iostream>
#include "raylib.h"

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    constexpr int SCREENWIDTH = 800;
    constexpr int SCREENHEIGHT = 450;

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Car Simulator");

    SetTargetFPS(60);
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

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}