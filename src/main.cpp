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

    Simulation::Car car {1000.0f, 20.0f, 40.0f};
    car.setPosition({200, 200});
    car.getRigidbody()->setRotation(90.0f);
    physicsWorld.addRigidbody(car.getRigidbody());
    car.getRigidbody()->setCollisionShape(std::make_unique<Physics::CollisionShapeRectangle>(20.0f, 40.0f));
    Rendering::CarRenderer carRenderer {};

    Simulation::Rectangle testKinematicBox {70.0f, 70.0f, 500.0f, 0.0f, {SCREENWIDTH/2.0f, SCREENHEIGHT/2.0f}};
    physicsWorld.addRigidbody(testKinematicBox.getRigidbody());
    Rendering::RectangleRenderer rectangleRenderer {70.0f, 70.0f, RED};

    Simulation::Rectangle testStaticRect {100.0f, 20.0f, 200.0f, 0.0f, {SCREENWIDTH/2.0f + 100.0f, SCREENHEIGHT/2.0f}, false};
    physicsWorld.addRigidbody(testStaticRect.getRigidbody());
    Rendering::RectangleRenderer testRectRenderer {100.0f, 20.0f, GREEN};

    Physics::Material asphaltMaterial {0.4f, 0.6f};
    Physics::Surface asphaltSurface {asphaltMaterial, std::make_unique<Physics::CollisionShapeRectangle>(SCREENWIDTH, SCREENHEIGHT)};
    asphaltSurface.getShapeMutable()->setCenter({SCREENWIDTH/2.0f, SCREENHEIGHT/2.0f});
    physicsWorld.addSurface(&asphaltSurface);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_F)) debugDraw.enabled = !debugDraw.enabled;

        float deltaTime = GetFrameTime();

        if (IsKeyDown(KEY_W))
        {
            car.setThrottle(1.f);
        }
        else
        {
            car.setThrottle(0.f);
        }
        if (IsKeyDown(KEY_A))
        {
            car.setSteeringAngle(-35);
        }
        else if (IsKeyDown(KEY_D))
        {
            car.setSteeringAngle(35);
        }
        else
        {
            car.setSteeringAngle(0);
        }

        car.step(deltaTime);
        physicsWorld.step(deltaTime);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        rectangleRenderer.draw(testKinematicBox.getPhysicsState());
        testRectRenderer.draw(testStaticRect.getPhysicsState());
        carRenderer.draw(car.getPhysicsState());

        debugDraw.drawAABB(car.getRigidbody());
        debugDraw.drawAABB(testKinematicBox.getRigidbody());
        auto wheels {car.getWheels()};
        auto wheelForces {car.getLateralForces()};
        for (int i = 0; i < 2; i++)
        {
            //std::cout << wheels[i].getWorldRotation(car.getRigidbody()) << std::endl;
            debugDraw.drawVector(wheelForces[i], car.getRigidbody()->getWorldPoint(wheels[i].getLocalPosition()));
        }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
