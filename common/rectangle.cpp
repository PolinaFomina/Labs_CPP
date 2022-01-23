#include "rectangle.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include "base-types.hpp"

fomina::Rectangle::Rectangle(double width, double height, const point_t& center, const double angle) :
  corners_{ { center.x - width / 2.0, center.y - height / 2.0 },
      { center.x - width / 2.0, center.y + height / 2.0 },
      { center.x + width / 2.0, center.y + height / 2.0 },
      { center.x + width / 2.0, center.y - height / 2.0 } }
{
  if ((width <= 0.0) || (height <= 0.0))
  {
    throw std::invalid_argument("Width and height must be > 0");
  }

  if (angle != 0)
  {
    rotate(angle);
  }
}

double fomina::Rectangle::getArea() const
{
  return getWidth() * getHeight();
}

fomina::rectangle_t fomina::Rectangle::getFrameRect() const
{
  double left = corners_[0].x;
  double right = corners_[0].x;
  double low = corners_[0].y;
  double upper = corners_[0].y;

  for (size_t i = 0; i < sizeof(corners_) / sizeof(corners_[0]); i++)
  {
    left = std::min(left, corners_[i].x);
    right = std::max(right, corners_[i].x);
    low = std::min(low, corners_[i].y);
    upper = std::max(upper, corners_[i].y);
  }

  return rectangle_t{ right - left, upper - low, { (right + left) / 2.0, (upper + low) / 2.0 } };
}

void fomina::Rectangle::move(const double dx, const double dy)
{
  for (size_t i = 0; i < sizeof(corners_) / sizeof(corners_[0]); i++)
  {
    corners_[i].x += dx;
    corners_[i].y += dy;
  }
}

void fomina::Rectangle::move(const point_t& center)
{
  move(center.x - getCenter().x, center.y - getCenter().y);
}

double fomina::Rectangle::getWidth() const
{
  return std::sqrt(std::pow(corners_[0].x - corners_[3].x, 2) + std::pow(corners_[0].y - corners_[3].y, 2));
}

double fomina::Rectangle::getHeight() const
{
  return std::sqrt(std::pow(corners_[0].x - corners_[1].x, 2) + std::pow(corners_[0].y - corners_[1].y, 2));
}

fomina::point_t fomina::Rectangle::getCenter() const
{
  return point_t{ (corners_[0].x + corners_[2].x) / 2.0, (corners_[0].y + corners_[2].y) / 2.0 };
}

void fomina::Rectangle::printInfo() const
{
  std::cout << "Rectangle's width: " << getWidth() << "\n"
      << "Rectangle's height: " << getHeight() << "\n"
      << "Rectangle's corners: ";
  for (size_t i = 0; i < sizeof(corners_) / sizeof(corners_[0]); i++)
  {
    std::cout << "(" << corners_[i].x << ", " << corners_[i].y << ") ";
  }
  std::cout << "\n";
  Shape::printInfo();
}

void fomina::Rectangle::scale(const double coef)
{
  if (coef <= 0.0)
  {
    throw std::invalid_argument("Coefficient must be > 0");
  }

  const point_t center_ = getCenter();
  for (size_t i = 0; i < sizeof(corners_) / sizeof(corners_[0]); i++)
  {
    corners_[i] = point_t{ center_.x + coef * (corners_[i].x - center_.x),
        center_.y + coef * (corners_[i].y - center_.y) };
  }
}

void fomina::Rectangle::rotate(const double angle)
{
  const point_t center = getCenter();
  for (size_t i = 0; i < sizeof(corners_) / sizeof(corners_[0]); i++)
  {
    details::rotatePoint(corners_[i], center, angle);
  }
}
