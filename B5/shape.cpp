#include "shape.hpp"

#include <iostream>
#include <iterator>
#include <cmath>

#include "reading-utility.hpp"
#include "point.hpp"

std::istream& operator>>(std::istream& in, Shape& shape)
{
  StreamGuard stream(in);
  size_t numberVertices;

  in >> std::noskipws;

  in >> std::ws >> numberVertices;
  if (in.fail())
  {
    return in;
  }

  Shape temp;
  for (size_t i = 0; i < numberVertices; i++)
  {
    Point point;
    in >> point;
    if (in.fail())
    {
      return in;
    }

    temp.push_back(point);
  }

  if (in.eof() || in.peek() == '\n')
  {
    shape = std::move(temp);
  }
  else
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}

std::ostream& operator<<(std::ostream& out, const Shape& shape)
{
  std::ostream::sentry sentry(out);
  if (sentry)
  {
    out << shape.size() << "  ";
    std::copy(shape.begin(), shape.end(), std::ostream_iterator<Point>(out, "  "));
  }

  return out;
}

bool isRectangle(const Shape& shape)
{
  if (shape.size() == NumberOfVertices::RECTANGLE_VERTICES)
  {
    const double side1 = std::sqrt(std::pow((shape[0].x - shape[1].x), 2) + std::pow((shape[0].y - shape[1].y), 2));
    const double side2 = std::sqrt(std::pow((shape[1].x - shape[2].x), 2) + std::pow((shape[1].y - shape[2].y), 2));
    const double side3 = std::sqrt(std::pow((shape[2].x - shape[3].x), 2) + std::pow((shape[2].y - shape[3].y), 2));
    const double side4 = std::sqrt(std::pow((shape[3].x - shape[0].x), 2) + std::pow((shape[3].y - shape[0].y), 2));
    const double diagonal1 = std::sqrt(std::pow((shape[0].x - shape[2].x), 2) + std::pow((shape[0].y - shape[2].y), 2));
    const double diagonal2 = std::sqrt(std::pow((shape[1].x - shape[3].x), 2) + std::pow((shape[1].y - shape[3].y), 2));

    return (side1 == side3) && (side2 == side4) && (diagonal1 == diagonal2);
  }

  return false;
}

bool isSquare(const Shape& shape)
{
  if (shape.size() == NumberOfVertices::RECTANGLE_VERTICES)
  {
    const double side1 = std::sqrt(std::pow((shape[0].x - shape[1].x), 2) + std::pow((shape[0].y - shape[1].y), 2));
    const double side2 = std::sqrt(std::pow((shape[1].x - shape[2].x), 2) + std::pow((shape[1].y - shape[2].y), 2));

    return isRectangle(shape) && (side1 == side2);
  }

  return false;
}

ShapePriority getPriority(const Shape& shape)
{
  if (shape.size() == NumberOfVertices::TRIANGLE_VERTICES)
  {
    return ShapePriority::TRIANGLE;
  }
  if (isSquare(shape))
  {
    return ShapePriority::SQUARE;
  }
  if (isRectangle(shape))
  {
    return ShapePriority::RECTANGLE;
  }
  else
  {
    return ShapePriority::OTHER;
  }
}
