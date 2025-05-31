# Path-Finding Algorithm
Implementation of the A* path-finding algorithm  for battle units to traverse a battlefield from a starting position to a target position. 

Algorithm was written and tested with C++ (C++17) and Microsoft Visual Studio Professional 2019 on Windows 11.

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
    -  A user defined or randomly positioned single battle unit. Assume that a unit always occupies exactly on poisiton on the battlefiled.
  
3. **Target Position**
    -  A user defined or randomly chosen target position for the unit.

**Note:** The algoritm supports the use of JSON format files compatible with [<ins>Risky Tilemap</ins>](https://riskylab.com/tilemap). A sample JSON is available at [<ins>this link</ins>](https://gist.github.com/dgehriger/80817b039498ed60657da048f980233f).

The layers[0].data field in this JSON format has *row x columns* entries, where:
* "0" represents the starting position for the battle unit
* "8" represents the target position (depending on icon set)
* "3" represents elevated terrain (depending on icon set)
* "-1" represents reachable positions

Output of the Algorithm
------------
* A list of positions for the battle unit to travel from its starting position to the target position.
* An ASCII representation of the traveled path in the grid from its starting positon to the target position.

Constraints of the Algorithm
------------
* The movement of a unit on the battlefield from one positon to the next is **discrete** and occurs in single steps. Units never occupy a position partially.
* Units can only **travel horizontally** (left-right) or **vertically** (forward-backward).
* The algorithm is capable of **backtracking** and finding a **valid path**, even in complex scenarios.

Future Improvements (TODO)
------------
Extend the algoritm to handle multiple units moving simultaneously:
* Units may move towards a common target position or to individual distanct target positions.
* At any given moment, each ground terrain position may be occupied by at most one unit.

Basic Usage
-----------
To instatiate the path-finding algorithm class
```cpp
    PathFinder::AStar astar;
```
To load a JSON file compatible with [<ins>Risky Tilemap</ins>](https://riskylab.com/tilemap)
```cpp
    astar.loadFile('your_JSON_filename_here.json');
```
To calculate the path from the starting position to the target positon
```cpp
    auto path = astar.findPath(PathFinder::heuristic::euclidean, 10);
```
To print the path as X,Y coordinates to the console window
```cpp
    astar.printPathCoords(path);
```

To draw the path to the console window using ASCII characters
```cpp
    astar.drawPath(path);
```

Development
------------

Layout:

    .
    |-- lib          # browser distribution (empty)
    |-- src          # source code (algorithms only)
    |-- test         # test scripts
    |-- utils        # build scripts (empty)
	|-- benchmark    # benchmarks (empty)
    `-- visual       # visualization (empty)

Usage and Results
------------

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
#### Results example

```cpp
Enter the JSON input filename (press Enter to use 'take_home_project.json'):

Opened file: take_home_project.json
Tile Size: 32 x 32
Value 0 (starting position) found at position: 220
Value 8 (target positon) found at position: 800
(X,Y) path coordinates
132 steps taken.
( 28 , 6 )
( 28 , 5 )
( 27 , 5 )
( 27 , 4 )
( 26 , 4 )
( 25 , 4 )
( 24 , 4 )
( 24 , 5 )
( 23 , 5 )
( 23 , 6 )
( 22 , 6 )
( 21 , 6 )
( 21 , 7 )
( 20 , 7 )
( 20 , 8 )
( 20 , 9 )
( 20 , 10 )
( 20 , 11 )
( 20 , 12 )
( 20 , 13 )
( 20 , 14 )
( 20 , 15 )
( 20 , 16 )
( 19 , 16 )
( 18 , 16 )
( 17 , 16 )
( 16 , 16 )
( 16 , 17 )
( 15 , 17 )
( 14 , 17 )
( 14 , 18 )
( 14 , 19 )
( 14 , 20 )
( 15 , 20 )
( 16 , 20 )
( 17 , 20 )
( 18 , 20 )
( 19 , 20 )
( 20 , 20 )
( 21 , 20 )
( 21 , 19 )
( 22 , 19 )
( 23 , 19 )
( 23 , 18 )
( 23 , 17 )
( 24 , 17 )
( 25 , 17 )
( 25 , 16 )
( 25 , 15 )
( 25 , 14 )
( 25 , 13 )
( 25 , 12 )
( 25 , 11 )
( 25 , 10 )
( 25 , 9 )
( 26 , 9 )
( 27 , 9 )
( 27 , 10 )
( 27 , 11 )
( 27 , 12 )
( 27 , 13 )
( 27 , 14 )
( 27 , 15 )
( 27 , 16 )
( 27 , 17 )
( 27 , 18 )
( 27 , 19 )
( 27 , 20 )
( 28 , 20 )
( 29 , 20 )
( 30 , 20 )
( 31 , 20 )
( 31 , 21 )
( 31 , 22 )
( 31 , 23 )
( 31 , 24 )
( 31 , 25 )
( 31 , 26 )
( 30 , 26 )
( 29 , 26 )
( 28 , 26 )
( 28 , 27 )
( 28 , 28 )
( 29 , 28 )
( 30 , 28 )
( 31 , 28 )
( 31 , 29 )
( 31 , 30 )
( 31 , 31 )
( 30 , 31 )
( 29 , 31 )
( 28 , 31 )
( 27 , 31 )
( 26 , 31 )
( 25 , 31 )
( 24 , 31 )
( 23 , 31 )
( 22 , 31 )
( 21 , 31 )
( 20 , 31 )
( 19 , 31 )
( 18 , 31 )
( 17 , 31 )
( 16 , 31 )
( 15 , 31 )
( 14 , 31 )
( 13 , 31 )
( 13 , 30 )
( 12 , 30 )
( 11 , 30 )
( 11 , 29 )
( 10 , 29 )
( 10 , 28 )
( 10 , 27 )
( 9 , 27 )
( 9 , 26 )
( 8 , 26 )
( 7 , 26 )
( 6 , 26 )
( 6 , 27 )
( 6 , 28 )
( 5 , 28 )
( 5 , 29 )
( 4 , 29 )
( 3 , 29 )
( 2 , 29 )
( 2 , 28 )
( 2 , 27 )
( 2 , 26 )
( 2 , 25 )
( 1 , 25 )
( 0 , 25 )
. . . X . . . . . . . X . . . . X . . . . . . . . . . X . X . .
. . . . X . . . X X X X . . . . X . X X X X X . X . . X . X . .
. . . . X . . . . . . . . . . . X . X . . . . . X X . . . X X X
. . . . X . . . X X X X X X . . X . X . X X X . . X X X . . . X
X X . . X . X X X . . . . X . . X . . X X . . . * * * * X X . X
. X X . . . X . . . . . . X X X X . X X . . . * * X . * * X . X
. . X . . . . X . X X X . X . . . . X . . * * * X X X . S X X X
. . X . . . . X . . . X . X . . . . . . * * X X X . X X . . . .
. . X X . . . X X . . X . X . . . X X X * X X . . . . X . . ? .
. . . X X . . . X . . X . . X . X . . X * X . . . * * * X . . .
. . . . . . . . X X . X X . X X . . . X * X . X . * X * X . . .
. . . . . . . . . X . . X . . X X . . X * X . X X * X * X X X X
X X X X X . . X X X . . X . . . X . . . * X . . X * X * X . X .
. . . . . X X . . . . . X X X X X X . . * X X X X * X * X . X .
. . . X X . . . . X . . . . . . . X . . * . . . X * X * X . X .
. . X X . . . . . X X X X . . . . . . . * . . X X * X * X . X .
. . X . . . . . . . . . X . . . * * * * * . X X . * X * X . X .
. X X . . . X . . X . . X . * * * X X X X X X * * * X * X . X .
. X . . . . X . . X X . X X * X X X . . . . . * X . . * . . X .
. . . . X X X . . . X . . X * X . . . . . * * * X X . * X X X .
X X X X . X . . . . X X . X * * * * * * * * X . . X X * * * * *
X . . X . X X X X . . X . X X X X . . X . . X X . . X X . . . *
. . . . . X . . X . . . X X . . X . X X . X . X . . . X X . . *
. X X . . X . . X . . . . X . . X . . . . X . X . . . . X X . *
. . X X . X . . X . . . . X . . . X X X X . . X . . . . . X . *
T * * X . X . . . X X . . . . X . . . . . . X X . X X X X X . *
. . * X X X * * * * X . . . . . . X X X X X X . . . . X * * * *
X X * X . . * X . * * X . . . . . X . . . . . . . . . X * X X X
. . * X . * * X . . * X X . . . X X X . X . . . X . . X * * * *
. . * * * * X X . . * * X X X . . . . . X X X X X . . X . . . *
. X X X X X X . . . . * * * X X X . . . . . . . . . . X . . . *
. X . . . . . . . . . . . * * * * * * * * * * * * * * * * * * *
Press any key to continue . . .
```

## Resources

* [A* algorithm](https://en.wikipedia.org/wiki/A*_search_algorithm)
* [Risky Tilemap](https://riskylab.com/tilemap)
* [Sample File](https://gist.github.com/dgehriger/80817b039498ed60657da048f980233f)
