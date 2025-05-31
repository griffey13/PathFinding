#pragma once

namespace PathFinder
{
	//----------------------------------------------------------------------------
	// class Point
	//----------------------------------------------------------------------------
	/*
	 * @brief   Defines a simple 2D Point.
	 * @details Simple 2-element vector D point class used for holding 2D 
	 *          coordinates of a grid 
	 */
	class Point
	{
	public:

		/*
		* @brief   Constructor using scalar initial values.
		* @param[in]   x   First vector element value (x).
		* @param[in]   y   Second vector element value (y).
		*/
		inline Point(int x, int y) : x(x), y(y) {}

		/*
		* @brief   Explicitly defaulted default constructor
		*/
		inline Point() = default;

		/*
		* @brief   Function operator == to determine if this vector is equal to another.
		* @details This compares each element on an element-by-element basis.
		* @param[in]   v  Input vector to compare against.
		* @return  True if each element of the vectors are equal.
		*/
		inline bool operator== (const Point& v) const { return (x == v.x) && (y == v.y); }

		/*
		* @brief   Function operator + to add two vectors.
		* @details Adds each element together on an element-by-element basis
		* @param[in]   v  Input vector to add to this vector
		* @return  The resultant vector.
		*/
		inline const Point operator+ (const Point& v) const { return Point(x + v.x, y + v.y); }

		/*
		* @brief   Function operator - to subtract two vectors.
		* @details Subtracts each element together on an element-by-element basis
		* @param[in]   v  Input vector to add to this vector
		* @return  The resultant vector.
		*/
		inline const Point operator- (const Point& v) const { return Point(x - v.x, y - v.y); }

		/*
		* @brief   Function to find vector difference
		* @details Absolute difference between each element on an element-by-element basis
	    * @param[in]   v1  The first vector.
	    * @param[in]   v2  The second vector.
		* @return  The resultant vector.
		*/
		static Point getDelta(const Point& v1, const Point& v2) { return Point(abs(v1.x - v2.x), abs(v1.y - v2.y)); }

		int x;  ///< First element of the vector.
		int y;  ///< Second element of the vector.
	};
}