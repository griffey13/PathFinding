#pragma once

#include <queue>
#include <vector>
#include <string>
#include <functional>
#include "Point.hpp"

namespace PathFinder
{
	using uint = unsigned int;
	using HeuristicFunction = std::function<uint(const Point&, const Point&, int)>;

	struct Node
	{
		/*
		* @brief   Constructor
		* @details Initialized with default values
		*/
		Node() : pos(0, 0), parent(-1, -1), f(0), g(0), h(0) {}

		/*
		* @brief   Constructor
		* @details Initialized with default values for values not provided
		* @param[in] pos  2D position of Node.
		* @param[in] f    Total cost function value
		*/
		Node(const Point& pos, uint f) : pos(pos), parent(-1, 1), f(f), g(0), h(0) {}

		/*
		* @brief Constructor
		* @param[in] pos     2D position of Node.
        * @param[in] parent  2D position of Node's parent
		* @param[in] f       Total cost function value
		* @param[in] g       Total cost function value
		* @param[in] g       Total cost function value
		*/
		Node(const Point& pos, const Point& parent, uint f, uint g, uint h) : pos(pos), parent(parent), f(f), g(g), h(h) {}

		Point pos;    /// 2D position of Node
		Point parent; /// Parent position of this Node
		uint f;       /// F = G + H (Total cost function)
		uint g;       /// Cost of the path from starting node to this node
		uint h;       /// Heuristic function cost estimate from this node to target node
	};

	/*
    * @brief Reverse std::priority_queue to get the smallest element on top
    * @param[in] a   First Node.
	* @param[in] b   Second Node.
	* @return True if first node huestic value greater than second node.
    */
	inline bool operator< (const Node& a, const Node& b) { return a.f > b.f; }

	//----------------------------------------------------------------------------
	// class AStar
	//----------------------------------------------------------------------------
	/*
	 * @brief Defines a simple A Star path finding algorithm with some
	 *        simple utility functions
	 */
	class AStar
	{
	public:

		/*
		* @brief Default constructor
		*/
		AStar();

		/*
		* @brief Find path from starting position (startPos) to target positon (targetPos) using
		*        A* algorithm
		* @param[in] weight Weight value used on heuristic function
		* @return Complete path from starting position to target position
		*/
		std::vector<Point> findPath(HeuristicFunction heuristicFunc, int weight = 1);

		/*
		* @brief Print path coordinates from starting position (startPos) to 
		*        target positon (targetPos) to console window as list of 2D coordinates
		*        and a file if desired
		* @note This function will always print to the console
		* @param[in] path Complete path from starting position to target position
		* @param[in] fileName Name of file to print to. Default is not to print to a file
		*/
		void printPathCoords(const std::vector<Point>& path, const std::string fileName = "");

		/*
		* @brief Draw path from starting position (startPos) to target positon (targetPos) to
		*        console window inside complete grid and a file if desired
        * @note This function will always print to the console
		* @param[in] path Complete path from starting position to target position
		* @param[in] fileName Name of file to print to. Default is not to print to a file
		*/
		void drawPath(const std::vector<Point>& path, const std::string fileName = "");

		/*
		* @brief Set the tile gird data
		* @param[in] dataIn The tile grid as read from JSON file
		* @param[in] xDim   The xDim of the tile grid
		* @param[in] yDim   The yDim of the tile grid
		*/
		void setTileData(const std::vector<int> dataIn, int xDim, int yDim);

		/*
		* @brief Set the starting position
		* @param[in] startPos The tile grid start postion
		*/
		void setStartPos(const Point& startPos) { m_startPos = startPos; }

		/*
		* @brief Set the target position
		* @param[in] targetPos The tile grid target postion
		*/
		void setTargetPos(const Point& targetPos) { m_targetPos = targetPos; }

		/*
		* @brief Load the JSON file
		* @param[in] fileName Name of JSON file to load
		* @return True if the file load successfully otherwise false
		*/
		bool loadFile(const std::string& fileName);

	private:

		/*
		* @brief   Builds the path
		*/
		std::vector<Point> buildPath() const;

		/*
		* @brief Determine if 2D tile cell is inside grid limts/dimensions
		* @param[in] pos 2D position in grid to check
		* @return True if cell is valid
		*/
		bool InsideGrid(const Point& pos) const;

		/*
		* @brief Determine if grid cell is walkable or blocked
		* @return True if cell is blocked/unwalkable
		*/
		bool isBlocked(int index) const { return (m_grid[index] == 3); }

		/*
		* @brief Returns a 1D index based on a 2D coordinate using row-major layout
		* @param[in] pos The 2D grid position to convert
		* @return The 1D flat position
		*/
		int convertTo1D(const Point& pos) const { return (pos.y * m_dimensions.x) + pos.x; }

		/*
		* @brief Returns a 2D index based on a 1D index using row-major layout
		* @param[in] pos The 1D grid position to convert
		* @return The 2D flat position
		*/
		Point convertTo2D(const int& pos) const;

		int m_weight;                            /// Weight used on heuristic function
		Point m_dimensions;                      /// X and Y dimensions of the grid. 
		Point m_startPos;                        /// Starting position for the path
		Point m_targetPos;                       /// Target position for the path
		std::priority_queue<Node> m_openList;    /// Open list queue of nodes
		std::vector<bool> m_closedList;          /// Closed list 
		std::vector<Node> m_cameFrom;            /// Came from list
		std::vector<int> m_grid;                 /// The tile grid
		std::vector<Point> m_directions;         /// All possible directions to take
		HeuristicFunction m_heuristic;           /// Heuristic function to be used
	};

	namespace heuristic
	{

		/*
		* @brief Calculate the Manhattan heuristic
		* @param[in] v1 The first grid position
		* @param[in] v2 The second grid position
		* @param[in] weight Heuristic weight value
		* @return The Manhattan heuristic value
		*/
		uint manhattan(const Point& v1, const Point& v2, int weight = 1);

		/*
		* @brief Calculate the Euclidean heuristic
		* @param[in] v1 The first grid position
		* @param[in] v2 The second grid position
		* @param[in] weight Heuristic weight value
		* @return The Euclidean heuristic value
		*/
		uint euclidean(const Point& v1, const Point& v2, int weight = 1);


		/*
		* @brief Calculate the Euclidean heuristic without the sqrt
		* @param[in] v1 The first grid position
		* @param[in] v2 The second grid position
		* @param[in] weight Heuristic weight value
		* @return The Euclidean heuristic value without the sqrt
		*/
		uint euclideanNoSQR(const Point& v1, const Point& v2, int weight = 1);

		/*
		* @brief Calculate the Dijkstra heuristic
		* @param[in] v1 The first grid position
		* @param[in] v2 The second grid position
		* @param[in] weight Heuristic weight value
		* @return The Dijkstra heuristic value
		*/
		uint dijkstra(const Point& v1, const Point& v2, int weight = 1);
	}
}
