#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace fomina
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const double width, const double height, const point_t& center, const double angle = 0.0);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const double dx, const double dy) override;
    void move(const point_t& center) override;
    double getWidth() const;
    double getHeight() const;
    point_t getCenter() const override;
    void printInfo() const override;
    void scale(const double coef) override;
    void rotate(const double angle) override;
  private:
    point_t corners_[4];
  };
}

#endif
