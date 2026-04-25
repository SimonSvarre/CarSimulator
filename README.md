# 🚗 CarSimulator

A 2D car physics simulator built with C++ and [raylib](https://www.raylib.com/).

---

## Prerequisites

You need the following installed before building:

| Tool | Version | Download |
|------|---------|----------|
| **CMake** | 3.16 or newer | https://cmake.org/download/ |
| **Git** | Any recent version | https://git-scm.com/ |
| **C++ Compiler** | C++20 support required | See below |

> **raylib is downloaded automatically** — you don't need to install it yourself.

### Compiler by platform

- **Windows** — Install [Visual Studio 2022](https://visualstudio.microsoft.com/) (select the "Desktop development with C++" workload), or [MinGW-w64](https://www.mingw-w64.org/)
- **macOS** — Run `xcode-select --install` in Terminal
- **Linux** — Run `sudo apt install build-essential` (Ubuntu/Debian) or the equivalent for your distro

---

## Build & Run

### 1. Clone the repository

```bash
git clone https://github.com/SimonSvarre/CarSimulator.git
cd CarSimulator
```

### 2. Configure with CMake

```bash
cmake -B build
```

> This step downloads raylib automatically. It may take a minute the first time.

### 3. Build

```bash
cmake --build build
```

### 4. Run

**Windows:**
```bash
.\build\Debug\CarSimulator.exe
```

**macOS / Linux:**
```bash
./build/CarSimulator
```

---

## Quick copy-paste (all steps at once)

```bash
git clone https://github.com/SimonSvarre/CarSimulator.git
cd CarSimulator
cmake -B build
cmake --build build
```

Then run the executable from the `build/` folder.

---

## How It Works

### Custom Physics Engine

The simulation includes a custom-built rigid body physics engine — no third-party physics library is used. It handles:

- Rigid body dynamics (forces, torques, linear & angular velocity)
- Collision detection and resolution between shapes (circles and rectangles)
- Surface friction and material properties

### Pacejka Tire Model ("Magic Formula")

Tire forces are calculated using the **Pacejka tire model**, a well-established model used in real vehicle dynamics research. It computes realistic lateral force, longitudinal force, and aligning torque based on slip angle and longitudinal slip.

The model is based on this paper from Stanford:
> H. Pacejka, E. Bakker, L. Nyborg — *Tyre modelling for use in vehicle dynamics studies* (SAE Paper No. 870421)
> [Reference PDF](http://www-cdr.stanford.edu/dynamic/bywire/tires.pdf)

This means the tires don't just apply a fixed friction force — they model how grip builds up and falls off realistically as the tire slips, which is what makes the car feel physically plausible.

---

## Project Structure

```
CarSimulator/
├── src/
│   ├── main.cpp
│   ├── math/               # Vector math utilities
│   ├── physics/            # Rigidbody, collision detection & resolution
│   ├── rendering/          # Car and debug rendering
│   └── simulation/         # Car, wheel, and shape logic
└── CMakeLists.txt
```

---

## Troubleshooting

**CMake can't find a compiler**
Make sure your compiler is installed and on your system PATH. On Windows, open the "Developer Command Prompt for VS 2022" and run the commands from there.

**Build fails on raylib download**
This can happen if Git isn't installed or you're behind a firewall. Make sure `git` is accessible from your terminal.

**`cmake -B build` gives a version error**
Update CMake to 3.16 or newer from https://cmake.org/download/.
