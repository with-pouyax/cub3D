# Project Rules

## General Requirements
- The project must be written in **C**.
- Follow the **42 Norm** coding style. Any norm error results in a grade of **0**.
- No unexpected crashes (**segfaults, bus errors, double frees, etc.**). Undefined behavior is the only exception.
- **Memory leaks are not allowed** – ensure all allocated memory is freed properly.

## Compilation & Makefile
- Use a **Makefile** that supports the following rules:
  - `all` – Compile the project.
  - `clean` – Remove object files.
  - `fclean` – Remove all compiled files.
  - `re` – Recompile everything.
  - `bonus` – Compile bonus features (if applicable).
- The Makefile **must not relink** object files unnecessarily.
- Compile using `cc` with the flags `-Wall -Wextra -Werror`.

## Mandatory Features
- Create a **3D graphical representation** of a maze using **ray-casting**.
- Use **miniLibX** for rendering.
- Implement smooth window management (switching, minimizing, etc.).
- Display walls with textures that change based on orientation (N, S, E, W).
- Set different colors for **floor and ceiling**.
- Support movement:
  - `W, A, S, D` for navigation.
  - Left/Right arrows for looking around.
  - `ESC` key to exit.
  - Clicking the **red cross** closes the window properly.
- Read a **.cub file** as input for scene configuration:
  - Valid characters: `0` (empty), `1` (wall), `N/S/E/W` (player spawn).
  - The map **must be enclosed by walls**.
  - **Textures and colors must be correctly defined** in the file.
  - If there is an error in the configuration file, the program must exit with an appropriate error message.

## Bonus Features (Evaluated Only if Mandatory Part is Perfect)
- **Wall collisions** to prevent passing through walls.
- **Minimap** showing an overview of the maze.
- **Doors** that can open and close.
- **Animated sprites**.
- **Mouse movement** to control the camera.

## Submission & Evaluation
- Submit all files to the assigned **Git repository**.
- Only the files in the repository will be evaluated.
- If grading is done using **Deepthought**, any error will cause the evaluation to stop.
- Peer evaluation will be conducted as per **42 guidelines**. 