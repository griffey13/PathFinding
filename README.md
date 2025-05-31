# PathFinding algorithm
Implementation of the A* path-finding algorithm written with C++ (C++17) and Microsoft Visual Studio Professional 2019.

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
