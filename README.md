[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://github.com/Malorn44/NurikabeMaker/blob/master/LICENSE)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/ce80ba03b87643fc8f90fbe0ea455e5a)](https://www.codacy.com/app/Malorn44/NurikabeMaker?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Malorn44/NurikabeMaker&amp;utm_campaign=Badge_Grade)

# NurikabeMaker
A GUI for auto-solving and auto-generating Nurikabe puzzles, along with solving them yourself.

![Application View](https://i.imgur.com/nHp0zIl.png)

### Generate Puzzles
This program can generate Nurikabe puzzles of any given size. The puzzles are guaranteed solvable but not guaranteed to have a single solution (yet).

Seen below is a 20x20 Nurikabe puzzle.

![Puzzle Example](https://i.imgur.com/mOVCOug.png)

### Manually Solve Puzzles
You can manually solve Nurikabe puzzles using this program with built-in undo/redo buttons, save states, and a solution checker that tells you what is incorrect about your solution (rooms of incorrect size, rooms without a number, unconnected walls, and 2x2 area of walls).

### Auto Solve Puzzles
The program can also *attempt* to manually solve puzzles.

## Running the Program
To run the program, simply double click the NurikabeMaker.exe file located in /build-NurikabeMaker-Desktop_Qt_5_12_1_MinGW_64_bit-Release/release/NurikabeMaker.exe

## Opening the project
Download Qt version 5.12.1+ along with Qt Creator version 4.8.2+

In Qt Creator, select File > New File or Project > Import Project > Import Existing Project

Choose a project name ("NurikabeMaker") and the location of the project.

## Acknowledgement
- Thanks to Stephan T. Lavavej and Microsoft for creating the current version of the solver (4/25/19) being used in this program. [His GitHub can be found here](https://github.com/Microsoft/nurikabe)
- Thanks to everyone working on TinyXML2 for making a publicly usable XML parser. [The TinyXML2 GitHub can be found here](https://github.com/leethomason/tinyxml2)
