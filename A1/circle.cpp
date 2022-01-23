#include "circle.hpp"
#include <iostream>
#include <cassert>

#define _USE_MATH_DEFINES

#include <cmath>

Circle::Circle(const point_t& center, const double radius) :
  center_(center),
  radius_(radius)
{
  assert(radius_ > 0.0);
}


double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{ 2 * radius_, 2 * radius_, center_ };
}

void Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Circle::move(const point_t& center)
{
  center_ = center;
}

point_t Circle::getCenter() const
{
  return center_;
}

double Circle::getRadius() const
{
  return radius_;
}

void Circle::printInfo() const
{
  std::cout << "Circle's radius: " << getRadius() << "\n";
  Shape::printInfo();
}
