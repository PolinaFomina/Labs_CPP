#include "base-types.hpp"

#define _USE_MATH_DEFINES

#include <cmath>

void fomina::details::rotatePoint(point_t& rotatingPoint, const point_t& staticPoint, const double angle)
{
  const double pointX = rotatingPoint.x;
  rotatingPoint.x = staticPoint.x + (pointX - staticPoint.x) * std::cos(angle * M_PI / 180)
      - (rotatingPoint.y - staticPoint.y) * std::sin(angle * M_PI / 180);
  rotatingPoint.y = staticPoint.y + (pointX - staticPoint.x) * std::sin(angle * M_PI / 180)
      + (rotatingPoint.y - staticPoint.y) * std::cos(angle * M_PI / 180);
}

bool fomina::details::areOverlapped(const rectangle_t& firstRectangle, const rectangle_t& secondRectangle)
{
  return ((std::abs(firstRectangle.pos.x - secondRectangle.pos.x) < (firstRectangle.width + secondRectangle.width) / 2.0)
      && (std::abs(firstRectangle.pos.y - secondRectangle.pos.y) < (firstRectangle.height + secondRectangle.height) / 2.0));
}
