# Path-Finding algorithm
Implementation of the A* path-finding algorithm  for battle units to traverse a battlefield from a starting position to a target position. 

Algorith was written and tested with C++ (C++17) and Microsoft Visual Studio Professional 2019 on Windows 11.

Introduction
------------

The aim of this project is to provide a path-finding library that can be easily implemented.

Note that this project only provides path-finding algorithms for 2D space.

Input to the Algorithm
------------
1. **Battlefield Map**
    -  A binary map of N x N fields, where each field represents a position on the battlefield
    -  Each position is either:
          - **Ground Terrain:** Occupiable by a single battle unit.
          - **Elevated Terrain:** Unreachable by battle units.
2. **Battle Unit**
    -  A user defined or randomly positioned single battle unit. Assume that a unit always occupies exactly on poisiton on the battlefiled
3. **Target Position**
    -  A user defined or randomly chosen target position for the unit.

**Note:** The algoritm supports the use of JSON format files compatible with [<ins>Risky Tilemap</ins>](https://riskylab.com/tilemap). A sample JSON is available at [<ins>this link</ins>](https://gist.github.com/dgehriger/80817b039498ed60657da048f980233f).

#### Usage example
```cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "AStar.h"
#include "Json.hpp"

using namespace std;

int main( int argc, char* argv[] )
{
    // Declare the filename variable.
    // Allow for a default file to be used
    string fileName;
    const string defaultFileName = "take_home_project.json";

    // Ask user for filename, allowing for a default via ENTER
    cout << "Enter the JSON input filename (press Enter to use '" << defaultFileName << "'): \n";
    getline(cin, fileName); 

    // If filename is empty, use default file
    if (fileName.empty())
        fileName = defaultFileName;

    // Create the pathfinder variable using A* algorithm
    PathFinder::AStar astar;
    astar.loadFile(fileName);
    auto path = astar.findPath(PathFinder::heuristic::euclidean, 10);

    // Print the path as X,Y coordinates to the console window
    astar.printPathCoords(path);

    // Draw the path to the console window using ASCII characters
    astar.drawPath(path);

    // Pause to ensure user can see output on console window
    system("pause");

    return 0;
}
```
