#include "AStar.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Json.hpp"

using namespace std;
using namespace placeholders;

// Simplify namespace access to JSON parser
using json = nlohmann::json;

namespace PathFinder
{
	AStar::AStar() :
		m_weight(1),
		m_dimensions(0, 0),
		m_startPos(0, 0),
		m_targetPos(0, 0),
		m_directions({ { -1,  0 }, { 1, 0 }, { 0, 1 }, { 0,  -1 } })
	{
	}

	bool AStar::loadFile(const string& fileName)
	{
		// Open the JSON file, report error
		ifstream file(fileName);
		if (!file.is_open()) {
			cerr << "Error: Could not open file: " << fileName << "\n";
			return false;
		}
		cout << "Opened file: " << fileName << "\n";

		// Parse the JSON file
		json jsonData;
		try {
			jsonData = json::parse(file);
		}
		catch (json::parse_error& e) {
			cerr << "JSON parse error: " << e.what() << "\n";
			return false;
		}

		// Parse the tilewidth x tileheight
		int tileWidth = -1;
		int tileHeight = -1;
		for (const auto& tileset : jsonData["tilesets"]) {
			tileWidth = tileset["tilewidth"];
			tileHeight = tileset["tileheight"];
			cout << "Tile Size: " << tileWidth << " x " << tileHeight << "\n";
		}
		if (tileWidth == -1 || tileHeight == -1 || tileWidth < 1 || tileHeight < 1)
		{
			cerr << "Error: Invalid Tile size: " << tileWidth << " x " << tileHeight << "\n";
			return false;
		}

		// Parse the layers
		auto layers = jsonData["layers"];
		vector<int> dataField;
		for (const auto& element : layers)
		{
			try
			{
				dataField = element.at("data").get<vector<int>>();
			}
			catch (const out_of_range& /* exception */)
			{
				cerr <<
					"Error in JSON data from `{}`: unknown layersType: '{}'.",
					file;
				return false;
			}
		}

		// Set the tile data 
		setTileData(dataField, tileWidth, tileHeight);

		// Find the starting position indicated by a value of 0 inside the grid
		int startPos;
		auto it = find(dataField.begin(), dataField.end(), 0);
		if (it != dataField.end()) {
			startPos = distance(dataField.begin(), it);
			cout << "Value " << 0 << " (starting position) found at position: " << startPos << endl;
		}
		else {
			cout << "Value " << 0 << " (starting position) not found in the tile." << endl;
			return false;
		}

		// Find the target position, indicated by a value of 8;
		int targetPos;
		it = find(dataField.begin(), dataField.end(), 8);
		if (it != dataField.end()) {
			targetPos = distance(dataField.begin(), it);
			cout << "Value " << 8 << " (target positon) found at position: " << targetPos << endl;
		}
		else {
			cout << "Value " << 8 << " (target positon) not found in the tile." << endl;
			return false;
		}

		//Close the file
		file.close();

		// Set the starting position and target position
		setStartPos(convertTo2D(startPos));
		setTargetPos(convertTo2D(targetPos));

		return true;
	}

	vector<Point> AStar::findPath(HeuristicFunction heuristicFunc, int weight)
	{
		// Initialize and set size of variables
		m_weight = weight;
		m_heuristic = bind(heuristicFunc, _1, _2, _3);
		m_cameFrom.resize(m_grid.size());
		m_closedList.resize(m_grid.size(), false);

		m_cameFrom[convertTo1D(m_startPos)].parent = m_startPos;
		m_openList.push(Node(m_startPos, 0));

		uint fNew, gNew, hNew;
		Point currentPos;

		while (!m_openList.empty())
		{
			// Get the node with the least f value
			currentPos = m_openList.top().pos;

			// Stop when target positon is reached
			if (currentPos == m_targetPos)
				break;

			// Remove current position from openlist via pop
			// Add current position to the closed list
			m_openList.pop();
			m_closedList[convertTo1D(currentPos)] = true;

			// Check the neighbors of the current node
			for (uint i = 0; i < 4; ++i)
			{
				const auto neighborPos = currentPos + m_directions[i];
				const auto neighborIndex = convertTo1D(neighborPos);

				if (!InsideGrid(neighborPos) || isBlocked(neighborIndex) || m_closedList[neighborIndex] == true)
					continue;

				// Cost of the path from start node to this node
				// Heuristic function to estimate cost from this node to target node 
				// Total cost
				gNew = m_cameFrom[convertTo1D(currentPos)].g + 1;
				hNew = m_heuristic(neighborPos, m_targetPos, m_weight);
				fNew = gNew + hNew;

				if (m_cameFrom[neighborIndex].f == 0 || fNew < m_cameFrom[neighborIndex].f)
				{
					m_openList.push(Node(neighborPos, fNew));
					m_cameFrom[neighborIndex] = { neighborPos, currentPos, fNew, gNew, hNew };
				}
			}
		}

		return buildPath();
	}

	vector<Point> AStar::buildPath() const
	{
		vector<Point> path;
		auto currentPos = m_targetPos;
		auto currentIndex = convertTo1D(currentPos);

		// Loop backwards from target position to start position
		while (!(m_cameFrom[currentIndex].parent == currentPos))
		{
			path.push_back(currentPos);
			currentPos = m_cameFrom[currentIndex].parent;
			currentIndex = convertTo1D(currentPos);
		}
		// Add start positon
		path.push_back(m_startPos);

		// Reverse order of path
		reverse(path.begin(), path.end());

		return path;
	}

	void AStar::printPathCoords(const vector<Point>& path, string fileName)
	{
		std::ofstream outputFile(fileName);
		bool bValidFile = false;

		// Open file
		if (outputFile.is_open())
			bValidFile = true;

		// Write to file
		cout                        << "(X,Y) path coordinates \n";
		if (bValidFile)  outputFile << "(X,Y) path coordinates \n";

		cout                       << path.size() << " steps taken \n";
		if (bValidFile) outputFile << path.size() << " steps taken \n";
		for (const auto& coord : path)
		{
			cout                       << "( " << coord.x << " , " << coord.y << " ) \n";
			if (bValidFile) outputFile << "( " << coord.x << " , " << coord.y << " ) \n";
		}

		// Close the file
		if (bValidFile) outputFile.close();
	}

	void AStar::drawPath(const vector<Point>& path, string fileName)
	{
		std::ofstream outputFile(fileName);
		bool bValidFile = false;

		// Open file
		if (outputFile.is_open())
			bValidFile = true;

		cout << "Visual depiction of Path traveled \n";
		cout << "LEGEND: \n";
		cout << "X = Wall \n";
		cout << "S = Start Postion \n";
		cout << "T = Target Position \n";
		cout << "* = Battle Unit Traveled Path \n";
		cout << ". = Walkable Grid Point \n";
		cout << "? = Unknown Grid Point, check Tile Map file \n";

		if (bValidFile) {
			outputFile << "Visual depiction of Path traveled \n";
			outputFile << "LEGEND: \n";
			outputFile << "X = Wall \n";
			outputFile << "S = Start Postion \n";
			outputFile << "T = Target Position \n";
			outputFile << "* = Battle Unit Traveled Path \n";
			outputFile << ". = Walkable Grid Point \n";
			outputFile << "? = Unknown Grid Point, check Tile Map file \n";
		}

		for (int yDim = 0; yDim < m_dimensions.y; ++yDim) {
			for (int xDim = 0; xDim < m_dimensions.x; ++xDim) {
				char c = '?';
				int pos = convertTo1D(Point(xDim, yDim));
				if (m_grid.at(pos) == 3)
					c = 'X'; // Wall
				else if (pos == convertTo1D(m_startPos))
					c = 'S'; // Starting position
				else if (pos == convertTo1D(m_targetPos))
					c = 'T'; // Target position
				else if (find(path.begin(), path.end(), Point(xDim, yDim)) != path.end())
					c = '*'; // Traversed path
				else if (m_grid.at(pos) == -1)
					c = '.'; // Walkable grid point
				cout                       << c << ' '; // Space delimited
				if (bValidFile) outputFile << c << ' '; // Space delimited
			}
		    cout                       << '\n';
			if (bValidFile) outputFile << '\n';
		}

		// Close the file
		if (bValidFile) outputFile.close();
	}

	void AStar::setTileData(const vector<int> dataIn, int xDim, int yDim)
	{
		m_dimensions.x = xDim;
		m_dimensions.y = yDim;
		m_grid = dataIn;
	}

	bool AStar::InsideGrid(const Point& pos) const
	{
		return (pos.x >= 0) && (pos.x < m_dimensions.x) &&
			(pos.y >= 0) && (pos.y < m_dimensions.y);
	}

	Point AStar::convertTo2D(const int& pos) const
	{
		int xPos = pos % m_dimensions.x;
		int yPos = pos / m_dimensions.x;

		return Point(xPos, yPos);
	}

	uint heuristic::euclidean(const Point& v1, const Point& v2, int weight)
	{
		const auto delta = Point::getDelta(v1, v2);
		return static_cast<uint>(weight * sqrt(pow(delta.x, 2) + pow(delta.y, 2)));
	}

	uint heuristic::manhattan(const Point& v1, const Point& v2, int weight)
	{
		const auto delta = Point::getDelta(v1, v2);
		return static_cast<uint>(weight * (delta.x + delta.y));
	}

	uint heuristic::euclideanNoSQR(const Point& v1, const Point& v2, int weight)
	{
		const auto delta = Point::getDelta(v1, v2);
		return static_cast<uint>(weight * (pow(delta.x, 2) + pow(delta.y, 2)));
	}

	uint heuristic::dijkstra(const Point& v1, const Point& v2, int weight)
	{
		const auto delta = Point::getDelta(v1, v2);
		return static_cast<uint>(weight * (pow(delta.x, 2) + pow(delta.y, 2)));
	}
}
