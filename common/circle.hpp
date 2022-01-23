#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace fomina
{
  class Circle : public Shape
  {
  public:
    Circle(const point_t& center, const double radius);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const double dx, const double dy) override;
    void move(const point_t& center) override;
    point_t getCenter() const override;
    double getRadius() const;
    void printInfo() const override;
    void scale(const double coef) override;
    void rotate(const double angle) override;
  private:
    point_t center_;
    double radius_;
  };
}

#endif
