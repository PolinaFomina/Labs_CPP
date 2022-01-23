#include "composite-shape.hpp"
#include <iostream>
#include <stdexcept>
#include <memory>
#include <algorithm>
#include "splitting.hpp"
#include "matrix.hpp"
#include "base-types.hpp"

fomina::CompositeShape::CompositeShape() :
  shapes_(nullptr),
  size_(0)
{}

fomina::CompositeShape::CompositeShape(const CompositeShape& compositeshape) :
  shapes_(nullptr),
  size_(0)
{
  if (compositeshape.size_)
  {
    shapes_ = std::make_unique<ShapePtr[]>(compositeshape.size_);
    size_ = compositeshape.size_;
    for (size_t i = 0; i < size_; i++)
    {
      shapes_[i] = compositeshape.shapes_[i];
    }
  }
}

fomina::CompositeShape::CompositeShape(CompositeShape&& compositeshape) :
  shapes_(std::move(compositeshape.shapes_)),
  size_(compositeshape.size_)
{
  compositeshape.size_ = 0;
}

fomina::CompositeShape& fomina::CompositeShape::operator=(const CompositeShape& compositeshape)
{
  if (this != &compositeshape)
  {
    if (compositeshape.size_)
    {
      shapes_ = std::make_unique<ShapePtr[]>(compositeshape.size_);
      size_ = compositeshape.size_;
      for (size_t i = 0; i < size_; i++)
      {
        shapes_[i] = compositeshape.shapes_[i];
      }
    }
    else
    {
      shapes_ = nullptr;
      size_ = 0;
    }
  }
  return *this;
}

fomina::CompositeShape& fomina::CompositeShape::operator=(CompositeShape&& compositeshape)
{
  if (this != &compositeshape)
  {
    if (compositeshape.size_)
    {
      shapes_ = std::move(compositeshape.shapes_);
      size_ = compositeshape.size_;
    }
    else
    {
       shapes_ = nullptr;
       size_ = 0;
    }
  }
  compositeshape.size_ = 0;
  return *this;
}

fomina::Shape::ShapePtr fomina::CompositeShape::operator[](const size_t index) const
{
  if (index >= size_)
  {
    throw std::invalid_argument("Index must be in the range [0, size_)");
  }

  return shapes_[index];
}

void fomina::CompositeShape::addShape(const ShapePtr& shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Shape is missing");
  }
  if (shape.get() == this)
  {
      throw std::invalid_argument("CompositeShape cannot contain itself");
  }

  ShapeArrayPtr temp = std::make_unique<ShapePtr[]>(size_ + 1);
  for (size_t i = 0; i < size_; i++)
  {
    temp[i] = shapes_[i];
  }
  shapes_ = std::move(temp);
  shapes_[size_] = shape;
  size_++;
}

void fomina::CompositeShape::deleteShape(const size_t index)
{
  if (index >= size_)
  {
    throw std::invalid_argument("Index must be in the range [0, size_)");
  }

  for (size_t i = index; i < size_ - 1; i++)
  {
    shapes_[i] = shapes_[i + 1];
  }
  size_--;
  shapes_[size_].reset();
}

double fomina::CompositeShape::getArea() const
{
  double area = 0.0;
  for (size_t i = 0; i < size_; i++)
  {
    area += shapes_[i]->getArea();
  }
  return area;
}

fomina::rectangle_t fomina::CompositeShape::getFrameRect() const
{
  if (size_ == 0)
  {
    return rectangle_t{ 0.0, 0.0, { 0.0, 0.0 } };
  }

  double left = shapes_[0]->getFrameRect().pos.x - (shapes_[0]->getFrameRect().width) / 2.0;
  double right = shapes_[0]->getFrameRect().pos.x + (shapes_[0]->getFrameRect().width) / 2.0;
  double low = shapes_[0]->getFrameRect().pos.y - (shapes_[0]->getFrameRect().height) / 2.0;
  double upper = shapes_[0]->getFrameRect().pos.y + (shapes_[0]->getFrameRect().height) / 2.0;

  for (size_t i = 1; i < size_; i++)
  {
    left = std::min(left, shapes_[i]->getFrameRect().pos.x - (shapes_[i]->getFrameRect().width) / 2.0);
    right = std::max(right, shapes_[i]->getFrameRect().pos.x + (shapes_[i]->getFrameRect().width) / 2.0);
    low = std::min(low, shapes_[i]->getFrameRect().pos.y - (shapes_[i]->getFrameRect().height) / 2.0);
    upper = std::max(upper, shapes_[i]->getFrameRect().pos.y + (shapes_[i]->getFrameRect().height) / 2.0);
  }

  return rectangle_t{ right - left, upper - low, {(right + left) / 2.0, (upper + low) / 2.0} };
}

void fomina::CompositeShape::move(const double dx, const double dy)
{
  for (size_t i = 0; i < size_; i++)
  {
    shapes_[i]->move(dx, dy);
  }
}

void fomina::CompositeShape::move(const point_t& center)
{
  move(center.x - getCenter().x, center.y - getCenter().y);
}

fomina::point_t fomina::CompositeShape::getCenter() const
{
  return getFrameRect().pos;
}

size_t fomina::CompositeShape::getSize() const
{
  return size_;
}

void fomina::CompositeShape::printInfo() const
{
  std::cout << "CompositeShape:" << "\n";
  Shape::printInfo();
  for (size_t i = 0; i < size_; i++)
  {
    std::cout << "Shape " << i << ":" << "\n";
    shapes_[i]->printInfo();
  }
}

void fomina::CompositeShape::scale(const double coef)
{
  if (coef <= 0.0)
  {
    throw std::invalid_argument("Coefficient must be > 0");
  }

  for (size_t i = 0; i < size_; i++)
  {
    shapes_[i]->move({ getCenter().x + coef * (shapes_[i]->getCenter().x - getCenter().x),
        getCenter().y + coef * (shapes_[i]->getCenter().y - getCenter().y) });
    shapes_[i]->scale(coef);
  }
}

void fomina::CompositeShape::rotate(const double angle)
{
  const point_t center = getCenter();
  for (size_t i = 0; i < size_; i++)
  {
    point_t move_point = shapes_[i]->getCenter();
    details::rotatePoint(move_point, center, angle);
    shapes_[i]->move(move_point);
    shapes_[i]->rotate(angle);
  }
}

fomina::Matrix fomina::CompositeShape::getPartition() const
{
  return splitIntoLayers(shapes_, size_);
}
