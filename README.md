# A* Path-Finding Algorithm
Implementation of the A* path-finding algorithm for battle units to traverse a battlefield from a starting position to a target position. 

Algorithm was written and tested with C++ (C++17) and Microsoft Visual Studio Professional 2019 on Windows 11.

**Note:** This repository aims to solve a take home project assignment for a job interview.

Setup
------------
To install and compile the program you will need an IDE, such as Visual Studio 2019, and a copy of the source code.
The code does not use any special libraries, and should be easily compiled.  

* Download the repository to your local machine
* Open the Visual Studio Solution **PathFinder.sln**
* Build the solution via **Build->Build Solution**
* Run the executable, **PathFinder.exe**
* A sample input file **take_home_project.json** is provided in the **Input** folder
* The output generated from the sample input file is provided in the **Output** folder

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
    -  A user defined or randomly positioned single battle unit. Assume that a unit always occupies exactly one position on the battlefield.
  
3. **Target Position**
    -  A user defined or randomly chosen target position for the unit.

**Note:** The algorithm supports the use of JSON format files compatible with [<ins>Risky Tilemap</ins>](https://riskylab.com/tilemap). A sample JSON is available at [<ins>this link</ins>](https://gist.github.com/dgehriger/80817b039498ed60657da048f980233f).

The layers[0].data field in this JSON format has *row x columns* entries, where:
* "0" represents the starting position for the battle unit
* "8" represents the target position (depending on icon set)
* "3" represents elevated terrain (depending on icon set)
* "-1" represents reachable positions

Heuristic function
----------

You can set the heuristic function to calculate the distance between two points and return the cost.

| Heuristic | C++ Function | Description |
|-----------|--------------|-------------|
| euclidean | PathFinder::Heuristic::euclidean | Default (shortest possible line between two points) |
| manhattan | PathFinder::Heuristic::manhattan | Sum of the absolute differences between the coordinates of the points |
| euclideanNoSQR | PathFinder::Heuristic::euclideanNoSQR | Euclidean heuristic without square root  |
| dijkstra | PathFinder::Heuristic::dijkstra | Always return 0 |

Output of the Algorithm
------------
* A list of positions for the battle unit to travel from its starting position to the target position.
* An ASCII representation of the traveled path in the grid from its starting position to the target position.

**Note:** The output can also be written to a file for future analysis.

Constraints of the Algorithm
------------
* The movement of a unit on the battlefield from one positon to the next is **discrete** and occurs in single steps. Units never occupy a position partially.
* Units can only **travel horizontally** (left-right) or **vertically** (forward-backward).
* The algorithm is capable of **backtracking** and finding a **valid path**, even in complex scenarios.

Future Improvements (TODO)
------------
Extend the algorithm to handle multiple units moving simultaneously:
* Units may move towards a common target position or to individual distinct target positions.
* At any given moment, each ground terrain position may be occupied by at most one unit.

Libraries
------------
Libraries used in this project.

[nlohmann::json](https://github.com/nlohmann/json)

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
To calculate the path from the starting position to the target position
```cpp
    auto path = astar.findPath(PathFinder::heuristic::euclidean, 10);
```
To print the path as X,Y coordinates to the console window
```cpp
    astar.printPathCoords(path);
```

To print the path as X,Y coordinates to a file
```cpp
    astar.printPathCoords(path, "yourFileNameHere.txt");
```

To draw the path to the console window using ASCII characters
```cpp
    astar.drawPath(path);
```

To draw the path to a file using ASCII characters
```cpp
    astar.drawPath(path, "yourFileNameHere.txt");
```

Development
------------

Layout:

    .
    
    |-- Input          # Input Files 
    |-- Output         # Ouput Files   
    |-- PathFinder     # Source Code
      |--Debug
    -- PathFinder.sln  # Visual Studio Solution File    
    --ReadMe.md        # Informative ReadMe file
    

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
    astar.printPathCoords(path, "PathOutput.txt");

    // Draw the path to the console window using ASCII characters
    astar.drawPath(path, "PathVisual.txt");

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
94 steps taken 
( 28 , 6 ) 
( 27 , 6 ) 
( 27 , 5 ) 
( 26 , 5 ) 
( 26 , 4 ) 
( 25 , 4 ) 
( 24 , 4 ) 
( 23 , 4 ) 
( 22 , 4 ) 
( 21 , 4 ) 
( 21 , 5 ) 
( 20 , 5 ) 
( 20 , 6 ) 
( 20 , 7 ) 
( 20 , 8 ) 
( 20 , 9 ) 
( 20 , 10 ) 
( 20 , 11 ) 
( 20 , 12 ) 
( 19 , 12 ) 
( 18 , 12 ) 
( 18 , 13 ) 
( 18 , 14 ) 
( 18 , 15 ) 
( 17 , 15 ) 
( 16 , 15 ) 
( 15 , 15 ) 
( 14 , 15 ) 
( 13 , 15 ) 
( 13 , 14 ) 
( 12 , 14 ) 
( 11 , 14 ) 
( 10 , 14 ) 
( 10 , 13 ) 
( 9 , 13 ) 
( 8 , 13 ) 
( 8 , 14 ) 
( 8 , 15 ) 
( 8 , 16 ) 
( 8 , 17 ) 
( 7 , 17 ) 
( 7 , 18 ) 
( 7 , 19 ) 
( 7 , 20 ) 
( 8 , 20 ) 
( 9 , 20 ) 
( 9 , 21 ) 
( 9 , 22 ) 
( 9 , 23 ) 
( 9 , 24 ) 
( 10 , 24 ) 
( 11 , 24 ) 
( 11 , 25 ) 
( 11 , 26 ) 
( 12 , 26 ) 
( 12 , 27 ) 
( 13 , 27 ) 
( 13 , 28 ) 
( 14 , 28 ) 
( 15 , 28 ) 
( 15 , 29 ) 
( 16 , 29 ) 
( 17 , 29 ) 
( 17 , 30 ) 
( 17 , 31 ) 
( 16 , 31 ) 
( 15 , 31 ) 
( 14 , 31 ) 
( 13 , 31 ) 
( 12 , 31 ) 
( 11 , 31 ) 
( 10 , 31 ) 
( 9 , 31 ) 
( 8 , 31 ) 
( 8 , 30 ) 
( 8 , 29 ) 
( 8 , 28 ) 
( 8 , 27 ) 
( 8 , 26 ) 
( 7 , 26 ) 
( 6 , 26 ) 
( 6 , 27 ) 
( 5 , 27 ) 
( 4 , 27 ) 
( 4 , 28 ) 
( 4 , 29 ) 
( 3 , 29 ) 
( 2 , 29 ) 
( 2 , 28 ) 
( 2 , 27 ) 
( 2 , 26 ) 
( 1 , 26 ) 
( 0 , 26 ) 
( 0 , 25 )
Visual depiction of Path traveled 
LEGEND: 
X = Wall 
S = Start Postion 
T = Target Position 
* = Battle Unit Traveled Path 
. = Walkable Grid Point 
? = Unknown Grid Point, check Tile Map file 
. . . X . . . . . . . X . . . . X . . . . . . . . . . X . X . . 
. . . . X . . . X X X X . . . . X . X X X X X . X . . X . X . . 
. . . . X . . . . . . . . . . . X . X . . . . . X X . . . X X X 
. . . . X . . . X X X X X X . . X . X . X X X . . X X X . . . X 
X X . . X . X X X . . . . X . . X . . X X * * * * * * . X X . X 
. X X . . . X . . . . . . X X X X . X X * * . . . X * * . X . X 
. . X . . . . X . X X X . X . . . . X . * . . . X X X * S X X X 
. . X . . . . X . . . X . X . . . . . . * . X X X . X X . . . . 
. . X X . . . X X . . X . X . . . X X X * X X . . . . X . . ? . 
. . . X X . . . X . . X . . X . X . . X * X . . . . . . X . . . 
. . . . . . . . X X . X X . X X . . . X * X . X . . X . X . . . 
. . . . . . . . . X . . X . . X X . . X * X . X X . X . X X X X 
X X X X X . . X X X . . X . . . X . * * * X . . X . X . X . X . 
. . . . . X X . * * * . X X X X X X * . . X X X X . X . X . X . 
. . . X X . . . * X * * * * . . . X * . . . . . X . X . X . X . 
. . X X . . . . * X X X X * * * * * * . . . . X X . X . X . X . 
. . X . . . . . * . . . X . . . . . . . . . X X . . X . X . X . 
. X X . . . X * * X . . X . . . . X X X X X X . . . X . X . X . 
. X . . . . X * . X X . X X . X X X . . . . . . X . . . . . X . 
. . . . X X X * . . X . . X . X . . . . . . . . X X . . X X X . 
X X X X . X . * * * X X . X . . . . . . . . X . . X X . . . . . 
X . . X . X X X X * . X . X X X X . . X . . X X . . X X . . . . 
. . . . . X . . X * . . X X . . X . X X . X . X . . . X X . . . 
. X X . . X . . X * . . . X . . X . . . . X . X . . . . X X . . 
. . X X . X . . X * * * . X . . . X X X X . . X . . . . . X . . 
T . . X . X . . . X X * . . . X . . . . . . X X . X X X X X . . 
* * * X X X * * * . X * * . . . . X X X X X X . . . . X . . . . 
X X * X * * * X * . . X * * . . . X . . . . . . . . . X . X X X 
. . * X * . . X * . . X X * * * X X X . X . . . X . . X . . . . 
. . * * * . X X * . . . X X X * * * . . X X X X X . . X . . . . 
. X X X X X X . * . . . . . X X X * . . . . . . . . . X . . . . 
. X . . . . . . * * * * * * * * * * . . . . . . . . . . . . . . 
Press any key to continue . . .
```

Contact
----------

For any questions, feedback, or suggestions, please contact me at [jacques.hoffler@gmail.com](mailto:jacques.hoffler@gmail.com).

**Note:** This repository aims to solve a take home project assignment for a job interview. 

## Resources

* [A* algorithm](https://en.wikipedia.org/wiki/A*_search_algorithm)
* [Risky Tilemap](https://riskylab.com/tilemap)
* [Sample File](https://gist.github.com/dgehriger/80817b039498ed60657da048f980233f)
