# C Programming Assignments - README

## Overview

This repository contains three C programming assignments that demonstrate fundamental programming concepts such as file handling, user interaction, and modularity. Each assignment builds on a specific use case, showcasing how C can be used for game development, feature implementation, and utility creation.

---

## Assignments

### **Assignment 1: Snake Game**
- **Description**:
  A classic snake game where the player can control the snake to navigate a grid-based map. The game includes a feature to make parts of the map darker for enhanced visual effects or challenges.
  
- **Features**:
  - Control the snake using user input.
  - Dynamically adjust the map's appearance to make areas dark.
  - Handles edge cases for invalid user input.
  
- **Files**:
  - `game.c`, `game.h`: Core logic for the snake game.
  - `map.c`, `map.h`: Map management and visual adjustments.
  - `terminal.c`, `terminal.h`: Terminal-based input and output.
  - `main.c`: Entry point for the program.
  - `makefile`: Automates compilation of the game.

- **How to Run**:
  1. Compile the program:
     ```bash
     make
     ```
  2. Run the game:
     ```bash
     ./game <map-file>
     ```

---

### **Assignment 2: Undo Feature for Snake Game**
- **Description**:
  Extends the snake game by adding the ability to undo the last step the snake took. This feature allows players to correct mistakes or explore alternate paths.
  
- **Features**:
  - Stores and tracks previous states to allow undoing actions.
  - Reads map configurations from external files (`map1.txt`, `map2.txt`, etc.).
  - Maintains the snake's state and reverts changes seamlessly.

- **Files**:
  - `game.c`, `game.h`: Extended logic to support undo functionality.
  - `undoFeature.c`, `undoFeature.h`: Implementation of the undo stack.
  - `mapX.txt`: Sample map configurations for testing.
  - `terminal.c`, `terminal.h`: User input and output handling.

- **How to Run**:
  1. Compile the program:
     ```bash
     make
     ```
  2. Run the game with undo support:
     ```bash
     ./game <map-file>
     ```
  3. Use the undo command during gameplay to revert actions.

---

### **Assignment 3: Messy Calculator**
- **Description**:
  A calculator program with minimal organization that handles basic arithmetic operations and extended functionality. While functional, this program showcases how lack of structure can complicate code management.

- **Features**:
  - Supports addition, subtraction, multiplication, and division.
  - Basic user input handling.
  - Limited error checking for invalid inputs.

- **Files**:
  - `main.c`: Contains the entire logic for the calculator, with no modularity or separation of concerns.

- **How to Run**:
  1. Compile the program:
     ```bash
     gcc main.c -o calculator
     ```
  2. Run the calculator:
     ```bash
     ./calculator
     ```

---

## Highlights

- **Snake Game**:
  - Demonstrates game mechanics in C.
  - Modular code structure for better maintenance.

- **Undo Feature**:
  - Uses stack-like data structures to track and revert game states.

- **Messy Calculator**:
  - Highlights the importance of clean code and modular design.

---

## Prerequisites

- GCC or any C compiler installed.
- A terminal or command-line environment to run the programs.

---

## Contribution

Contributions to improve code structure, add new features, or refactor the messy calculator are welcome! Feel free to submit a pull request.

---

## Contact

For questions or clarifications, please contact the repository maintainer.

---

*Enjoy learning and exploring C programming!* 🐍 🎮 ✏️
