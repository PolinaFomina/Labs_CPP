#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <memory>

namespace fomina
{
  struct point_t;
  struct rectangle_t;
  class Shape
  {
  public:
    using ShapePtr = std::shared_ptr<Shape>;
    using ShapeArrayPtr = std::unique_ptr<ShapePtr[]>;
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const double dx, const double dy) = 0;
    virtual void move(const point_t& center) = 0;
    virtual point_t getCenter() const = 0;
    virtual void printInfo() const = 0;
    virtual void scale(const double coef) = 0;
    virtual void rotate(const double angle) = 0;
  };
}

#endif
