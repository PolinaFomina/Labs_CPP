#include "rectangle.hpp"
#include <iostream>
#include <cassert>

Rectangle::Rectangle(const double width, const double height, const point_t& center):
  width_(width),
  height_(height),
  center_(center)
{
  assert((width_ > 0.0) && (height_ > 0.0));
}


double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rectangle_t{ width_, height_, center_ };
}

void Rectangle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Rectangle::move(const point_t& center)
{
  center_ = center;
}

double Rectangle::getWidth() const
{
  return width_;
}

double Rectangle::getHeight() const
{
  return height_;
}

point_t Rectangle::getCenter() const
{
  return center_;
}

void Rectangle::printInfo() const
{
  std::cout << "Rectangle's width: " << getWidth() << "\n"
      << "Rectangle's height: " << getHeight() << "\n";
  Shape::printInfo();
}
