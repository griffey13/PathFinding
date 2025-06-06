# A* Path-Finding Algorithm
Implementation of the A* path-finding algorithm for battle units to traverse a battlefield from a starting position to a target position. 

Algorithm was written and tested with C++ (C++17) and Microsoft Visual Studio Professional 2019 on Windows 11.

**Note:** This repository aims to solve a take home project assignment for a job interview.

Introduction
------------

The aim of this project is to provide a path-finding library that can be easily implemented.

**Note:** This project only provides path-finding algorithms for 2D space.

Setup
------------
To install and compile the program you will need to use an IDE, such as Visual Studio 2019, and a copy of the source code.
The code use a third party library to parse JSON files, and should be easily compiled.  

* Download the repository to your local machine
* Open the Visual Studio Solution **PathFinder.sln**
* Build the solution via **Build->Build Solution**
* Run the executable, **PathFinder.exe**
* A sample input file **take_home_project.json** is provided in the **Input** folder
* The output generated from the sample input file is provided in the **Output** folder as **take_home_project.txt**

# A* Coding Summary
- Once a node is chosen, it is guaranteed to be the optimal path from the previous node to the current node since the heuristic is consistent and the best possible _g(h)_ and _f(h)_ is choosen for this node. This current node is then added to the closed set and will be ignored if encountered again as a neighbor of another node during future computations.
- Next the algorithm explores the _neighbors_ of the current node. Each current node can have 4 neighbors. For the 4 neighbor nodes we can:
    -  Ignore it if it is in the closed list
    -  Ignore it if it is a **Elevated Terrain** which is unreachable by battle units
    -  Ignore it if it is outside the battlefield grid
    -  Perform calculations to determine if going from _start_ to _neighbor_ having the current node as its parent node in the path is more optimal than the path that has been calculated so far for _neighbor_. If so, the information for _neighbor_ is updated:
          -  Its new _g(h)_ is easily calculated knowing the definitve g-score of _current_ and _neighbor_ is adjacent to _current_.
          -  Its new _f(h)_ is easily calculated since the h-score is fixed.
          - The _cameFrom_ list is updated by updating or creating the key _neighbor_ with the value _current_. This method to only keep the _parent_ of each node and reconstructing the path backwards is better than keeping all the partial paths: it saves memory, and the reconstruction algorithm is linear, so it is fast and suitable for **Real Time Systems**.
- Iterate on the process until reaching the _Target_ position

Input to the Algorithm
------------
1. **Battlefield Map**
    -  A binary map of N x N fields, where each field represents a position on the battlefield.
        - **Note:** The current implementation allows for a binary map of N X M fields. 
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
| dijkstra | PathFinder::Heuristic::dijkstra | Placeholder for now. Always return 0 |

Output of the Algorithm
------------

| Output | Description | Note |
|-----------|--------------|-------------|
| File | A list of positions the battle unit traveled from its starting position to the target position | Optional output. Filename provided by user. |
| File | An ASCII representation of the traveled path in the grid from its starting position to the target position | Optional output. Filename provided by user. |
| Console Window | Contents of optional output files pretty printed to the terminal window. | Always printed  |

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

## File Descriptions
| Class            | Description                                                                          | Location  |
| ---------------- | ------------------------------------------------------------------------------------ |-----------|
| Point            | A simple 2-element vector point class used for holding 2D corrdinates of a grid.     | Point.hpp  |
| AStar            | Contains the actual A* algorithm, used to search the 2D grid and retrieve the optimal trajectory that solves the problem.| AStar.h, AStar.cpp |

| Namespace        | Description                                                                          | Location  |
| ---------------- | ------------------------------------------------------------------------------------ |-----------|
| heuristic        | Contains a function that computes the heuristic of a battle unit, i.e. the estimate of the distance from the current location to the goal. | AStrar.h, AStar.cpp |
| Pathfinder            | Contains the _AStar_ and _Point_ class | Astar.hpp, Astar.cpp |

| File             | Description                                                                          |
| ---------------- | ------------------------------------------------------------------------------------ |
| take_home_project.json      | JSON file containing 2D battlefield grid and battle unit information  |
| Sample1.json      | JSON file containing simple 2D battlefield grid and battle unit information for testing  |
| Sample2.json      | JSON file containing simple 2D battlefield grid and battle unit information for testing  |
| Sample3.json      | JSON file containing simple 2D battlefield grid and battle unit information for testing  |
| PathOutput.txt    | Results presenting path coordinates after from processing _take_home_project.json_  |
| PathVisual.txt    | Results presenting visual depiction after from processing _take_home_project.json_  |
| Sample1_PathOutput.txt    | Results presenting path coordinates after from processing _Sample1.json_  |
| Sample1_PathVisual.txt    | Results presenting visual depiction after from processing _Sample1.json_  |
| Sample2_PathOutput.txt    | Results presenting path coordinates after from processing _Sample2.json_  |
| Sample2_PathVisual.txt    | Results presenting visual depiction after from processing _Sample2.json_  |
| Sample3_PathOutput.txt    | Results presenting path coordinates after from processing _Sample3.json_  |
| Sample3_PathVisual.txt    | Results presenting visual depiction after from processing _Sample3.json_  |
| main.cpp         | For demonstrating the usage of the Astar program in a practical scenario. |


Libraries
------------
This project uses a a third party JSON library which provides an API for manipulating and parsing JSON files which can be located at [nlohmann::json](https://github.com/nlohmann/json)

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

An alternative to loading a JSON file to obtain the battlefield grid is to directly specify the battlergrid  as provided below
```cpp
    std::vector<int> dataField = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                   -1, -1, -1,  3,  3, 3, -1, -1, -1, -1, 
                                   -1, -1, -1,  3, -1, -1, -1, -1, -1, -1, 
                                   -1, -1, -1,  3, -1, -1, -1, -1, -1, -1, 
                                   -1, -1, -1,  3, -1, -1, -1, -1, -1, -1, 
                                   -1, -1,  8,  3,  0, -1, -1, -1, -1, -1, 
                                   -1, -1, -1,  3, -1, -1, -1, -1, -1, -1, 
                                   -1, -1, -1,  3, -1, -1, -1, -1, -1, -1, 
                                   -1, -1, -1,  3,  3,  3,  3,  3,  3, -1, 
                                   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
    astar.setTileData(dataField, 10, 10);

    // Find the starting position indicated by a value of 0 inside the grid
    if (!getStartPos(dataField)) return false;

    // Find the target position, indicated by a value of 8;
    if (!getTargetPos(dataField)) return false;
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
    |-- Output         # Output Files   
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
