cmake_minimum_required(VERSION 3.31)
project(CarSimulator)

set(CMAKE_TOOLCHAIN_FILE "/opt/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

add_executable(CarSimulator src/main.cpp
        src/physics/Rigidbody.cpp
        src/physics/Rigidbody.h
        src/physics/PhysicsMath.h
        src/rendering/CarRenderer.cpp
        src/rendering/CarRenderer.h
        src/rendering/Renderer.cpp
        src/rendering/Renderer.h
        src/simulation/car/Car.cpp
        src/simulation/car/Car.h
        src/simulation/car/Wheel.cpp
        src/simulation/car/Wheel.h
        src/physics/PhysicsWorld.cpp
        src/physics/PhysicsWorld.h)

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