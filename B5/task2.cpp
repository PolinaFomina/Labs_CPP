#include <iostream>
#include <vector>
#include <iterator>
#include <stdexcept>
#include <numeric>
#include <algorithm>

#include "shape.hpp"
#include "point.hpp"

void task2(std::istream& in, std::ostream& out)
{
  std::vector<Shape> shapes((std::istream_iterator<Shape>(in)), std::istream_iterator<Shape>());

  if (!in.eof())
  {
    throw std::runtime_error("Read error");
  }

  size_t numberOfVertices = std::accumulate(shapes.begin(), shapes.end(), 0,
      [](size_t sum, const Shape& shape) { return sum += shape.size(); });

  size_t numberOfTriangles = std::count_if(shapes.begin(), shapes.end(),
      [](const Shape& shape) { return shape.size() == NumberOfVertices::TRIANGLE_VERTICES; });

  size_t numberOfSquares = std::count_if(shapes.begin(), shapes.end(),
      [](const Shape& shape) { return isSquare(shape); });

  size_t numberOfRectangles = std::count_if(shapes.begin(), shapes.end(),
      [](const Shape& shape) { return isRectangle(shape); });

  shapes.erase(std::remove_if(shapes.begin(), shapes.end(),
      [](const Shape& shape) { return shape.size() == NumberOfVertices::PENTAGON_VERTICES; }), shapes.end());

  std::vector<Point> points;

  std::for_each(shapes.begin(), shapes.end(),
      [&points](const Shape& shape) { points.push_back(shape[0]); });

  std::sort(shapes.begin(), shapes.end(),
      [](const Shape& shape1, const Shape& shape2) { return getPriority(shape1) < getPriority(shape2); });

  out << "Vertices: " << numberOfVertices << '\n'
      << "Triangles: " << numberOfTriangles << '\n'
      << "Squares: " << numberOfSquares << '\n'
      << "Rectangles: " << numberOfRectangles << '\n';

  out << "Points: ";
  std::copy(points.begin(), points.end(), std::ostream_iterator<Point>(out, " "));

  out << '\n' << "Shapes: " << '\n';
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape>(out, "\n"));
}
