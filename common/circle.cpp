#include "circle.hpp"
#include <stdexcept>
#include <iostream>

#define _USE_MATH_DEFINES

#include <cmath>
#include "base-types.hpp"

fomina::Circle::Circle(const point_t& center, const double radius) :
  center_(center),
  radius_(radius)
{
  if (radius_ <= 0.0)
  {
    throw std::invalid_argument("Radius must be > 0");
  }
}


double fomina::Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

fomina::rectangle_t fomina::Circle::getFrameRect() const
{
  return rectangle_t{ 2 * radius_, 2 * radius_, center_ };
}

void fomina::Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void fomina::Circle::move(const point_t& center)
{
  center_ = center;
}

fomina::point_t fomina::Circle::getCenter() const
{
  return center_;
}

double fomina::Circle::getRadius() const
{
  return radius_;
}

void fomina::Circle::printInfo() const
{
  std::cout << "Circle's radius: " << getRadius() << "\n";
  Shape::printInfo();
}

void fomina::Circle::scale(const double coef)
{
  if (coef <= 0.0)
  {
    throw std::invalid_argument("Coefficient must be > 0");
  }
  radius_ *= coef;
}

void fomina::Circle::rotate(const double)
{
}
