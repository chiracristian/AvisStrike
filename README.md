# AvisStrike

**AvisStrike** is a high-performance, modular 2D combat engine and arcade shooter. It shifts the focus from static gameplay to **creative engineering**, allowing users to design, validate, and pilot custom-built spacecraft through an intuitive grid-based interface.

Built with **C++** and **OpenGL**, AvisStrike emphasizes clean architectural patterns, structural graph theory for vessel validation, and a procedural approach to 2D rendering.

## Core Systems

### 1. The Modular Hangar (Editor)

The **Ship Construction Suite** provides a workspace to assemble functional vessels from distinct modules.

* **Structural Blocks**: Provide the framework and connectivity for the ship.
* **Engine Modules**: Dictate flight maneuverability and top speed.
* **Turret Modules**: Determine offensive capabilities.

### 2. The Structural Validation Engine

The software treats the ship as a mathematical graph to ensure mechanical viability before deployment:

| Constraint | Technical Logic |
| --- | --- |
| **Connectivity** | A **Depth-First Search (DFS)** verifies that every placed module is part of a single continuous entity. |
| **Firing Clearance** | The engine checks for structural obstructions in the vector path above every turret. |
| **Exhaust Path** | Ensures no modules are placed behind engines, preventing structural interference with propulsion. |
| **Functional Minimum** | Validates the presence of at least one engine and one turret for basic combat readiness. |

### 3. Dynamic Combat & Economy

The difficulty scales dynamically, increasing enemy movement frequency and fire rates as waves progress.

* **The Reward System**: Currency is earned based on performance. Higher waves yield higher rewards per enemy defeated ($Reward = \text{Wave Count}$).
* **Component Upgrades**: Modules are upgraded in the hangar to improve baseline stats using a linear progression model.

## Technical Deep Dive

### Procedural Primitive Generation

AvisStrike utilizes a `ShapeFactory` to generate geometry at runtime. Instead of relying on static textures, it procedurally constructs vertices and indices for circles, ellipses, and complex polygons. The `Shape` class supports merging elementary building blocks, allowing for perfectly scaled UI elements with **only one draw call per entity**.

### Object Lifecycle & Optimization

To maintain high performance during intense waves, the engine uses a **Swap-and-Pop** strategy for entity management:

* Entities (projectiles, enemies) are stored in contiguous memory.
* When an entity is destroyed, it is swapped with the last element in the vector and popped, ensuring **$O(1)$ removal time** without invalidating the rest of the collection.

### Physics & Collision

The collision system is a hybrid of **Axis-Aligned Bounding Boxes (AABB)** for structural components and **Circle-to-Circle** intersection tests for projectiles and enemies. This provides high-speed detection while maintaining gameplay "feel."

## Controls

| Mode | Action | Key/Input |
| --- | --- | --- |
| **Hangar** | Place Component | `Left Click` (Drag & Drop) |
| **Hangar** | Remove Component | `Right Click` |
| **Combat** | Movement | `W`, `A`, `S`, `D` / `Arrow Keys` |
| **Combat** | Fire Turrets | `Spacebar` |
| **Combat** | Pause | `P` |
| **Combat** | Reset | `R` (After Game Over) |
| **System** | Exit | `ESC` |

## Building from Source

AvisStrike uses **CMake** for build automation.

1. **Install Dependencies**: Scripts for Ubuntu, Fedora, Arch, and macOS are located in the `/tools` directory.
2. **Build**:
```bash
mkdir build && cd build
cmake ..
make

```

3. **Run**: Execute the binary generated in the root or build folder.

## Project Structure

```text
AvisStrike/
├── assets/                # Shaders and UI fonts
├── docs/                  # Developer & User documentation
├── infra/                 # CMake build utilities
├── src/
│   ├── lab_m1/            # CUSTOM GAME LOGIC
│   │   └── Tema1/
│   │       ├── entities/  # Behavior & Collision logic
│   │       ├── shapes/    # Procedural mesh generation (ShapeFactory)
│   │       └── ...        # State management & Validation engine
│   ├── core/              # OpenGL GPU/Buffer management
│   ├── components/        # Camera, Input, and Text subsystems
│   └── utils/             # Math and GL helper utilities
└── tools/                 # Cross-platform dependency & install scripts
```

## Licensing & Acknowledgements

* **License**: This project is licensed under the **MIT License**.

* **Attribution**: All source code located under `src/lab_m1` (the core gameplay logic, modular editor, and structural validation systems) was developed by Cristian-Ioan-George Chira.

* **Framework**: This project utilizes the **UPB-Graphics** framework ([GitHub](https://github.com/UPB-Graphics/gfx-framework)).

* **Context**: Project architecture and implementation were inspired by the **Elements of Computer Graphics** labs at the *National University of Science and Technology Politehnica Bucharest* ([EGC Labs](https://ocw.cs.pub.ro/courses/egc)).
