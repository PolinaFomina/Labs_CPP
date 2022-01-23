#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <vector>
#include <iostream>

#include "point.hpp"

enum NumberOfVertices
{
  TRIANGLE_VERTICES = 3,
  RECTANGLE_VERTICES = 4,
  PENTAGON_VERTICES = 5
};

enum ShapePriority
{
  TRIANGLE,
  SQUARE,
  RECTANGLE,
  OTHER
};

using Shape = std::vector<Point>;

std::istream& operator>>(std::istream& in, Shape& point);
std::ostream& operator<<(std::ostream& out, const Shape& point);
bool isRectangle(const Shape& shape);
bool isSquare(const Shape& shape);
ShapePriority getPriority(const Shape& shape);

#endif
