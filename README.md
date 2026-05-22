*This project has been created as part of the 42 curriculum by andrrand, mrakotos.*

# cub3D

## Description

cub3D is a graphic programming project from the 42 curriculum inspired by the famous game Wolfenstein 3D, one of the first First-Person Shooters ever created.

The goal of the project is to build a simple 3D game engine using the raycasting technique and the MiniLibX graphical library.  
The player can move inside a maze from a first-person perspective while the engine renders walls with different textures depending on their orientation.

This project helped us improve our knowledge in:
- Raycasting
- Mathematics for graphics
- Event handling
- Parsing
- Memory management
- Window management with MiniLibX
- Game loop and frame management

## Features

### Mandatory Part
- Raycasting-based 3D rendering
- Different wall textures (North, South, East, West)
- Floor and ceiling colors
- Player movement with `W`, `A`, `S`, `D`
- Camera rotation with left/right arrows
- `.cub` map parsing
- Map validation
- Clean window management
- Memory leak free

### Bonus Part
Not implemented.

## Controls

| Key | Action |
|---|---|
| W | Move forward |
| S | Move backward |
| A | Move left |
| D | Move right |
| ← / → | Rotate camera |
| ESC | Exit the game |

## Instructions

### Requirements

- Linux
- GCC / CC
- Make
- MiniLibX
- X11 libraries

### Compilation

```bash
make
```

### Run

```bash
./cub3D map.cub
```

### Cleaning

```bash
make clean
make fclean
make re
```

## Map Format

The program accepts a `.cub` configuration file containing:
- Texture paths
- Floor and ceiling colors
- The game map

Example:

```txt
NO ./assets/textures/north.xpm
SO ./assets/textures/south.xpm
WE ./assets/textures/west.xpm
EA ./assets/textures/east.xpm

F 220,100,0
C 225,30,0

111111
100001
10N001
100001
111111
```

Allowed map characters:
- `1` → Wall
- `0` or space → Empty space
- `N`, `S`, `E`, `W` → Player spawn position

## Technical Choices

- DDA algorithm for raycasting
- Custom parser for `.cub` files
- Delta time management for smoother movements
- Texture rendering using MiniLibX images
- Modular project structure

## Resources

### Documentation & Tutorials
- https://lodev.org/cgtutor/raycasting.html
- https://github.com/42Paris/minilibx-linux

### AI Usage

AI tools were used to:
- Better understand raycasting concepts
- Learn MiniLibX behavior
- Get explanations about mathematical formulas
