*This project has been created as part of the 42 curriculum by nalesso, arhea.*

# cub3D

## Description

A 3D raycaster inspired by Wolfenstein 3D, built using the miniLibX graphics library. This project renders a first-person view of a maze defined in a `.cub` configuration file, featuring textured walls and configurable floor/ceiling colors. The goal is to explore the fundamentals of raycasting to create a realistic 3D graphical representation from a 2D map.

## Instructions

**Compilation:**
```bash
make        # Compile the project
make clean  # Remove object files
make fclean # Remove all generated files
make re     # Recompile from scratch
```

**Execution:**
```bash
./cub3D <map.cub>
```
The map file must have a `.cub` extension and contain:
- Texture paths (NO, SO, WE, EA)
- Floor and ceiling colors (F, C) in RGB format
- A valid map with walls (1), spaces (0), and one player position (N, S, E, or W)

**Controls:**
- `W` `A` `S` `D` — Movement
- `←` `→` — Camera rotation
- `ESC` — Exit

## Resources

**Core Raycasting:**
- [Ray-Casting Tutorial - Lode Vandevenne](https://lodev.org/cgtutor/raycasting.html) — Complete raycasting implementation: DDA algorithm, camera plane, wall rendering, and fisheye correction
- [Ray-Casting Tutorial - F. Permadi](https://permadi.com/tutorial/raycast/) — Classic 1996 tutorial covering theory, projection, finding walls, textures, floors, and movement

**Vectors, Matrices & Rotation:**
- [LearnOpenGL: Transformations](https://learnopengl.com/Getting-started/Transformations) — Vectors, matrices, rotation matrices with sine/cosine, scaling, and translation explained for graphics programming
- [3Blue1Brown: Essence of Linear Algebra](https://www.youtube.com/playlist?list=PLZHQObOWTQDPD3MizzM2xVFitgF8hE_ab) — Visual explanation of vectors, linear transformations, and matrix operations
- [Math is Fun: Matrices](https://www.mathsisfun.com/algebra/matrix-introduction.html) — Basic matrix operations (addition, multiplication, transpose)

**Graphics & Pixel Rendering:**
- [miniLibX Documentation - 42Docs](https://harm-smits.github.io/42docs/libs/minilibx) — Graphics library for window management, hooks, and pixel drawing

**AI Usage:**
AI tools (GitHub Copilot, Claude) were used for:
- Generation of XPM texture files (Python scripts to create wall textures)
- Code review and debugging assistance
- Documentation and README writing