cmake_minimum_required(VERSION 3.31)
project(CarSimulator)

set(CMAKE_TOOLCHAIN_FILE "/opt/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

add_executable(CarSimulator src/main.cpp)

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