#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include "shape.hpp"

namespace fomina
{
  struct point_t;
  struct rectangle_t;
  class Matrix;
  class CompositeShape : public Shape
  {
  public:
    CompositeShape();
    CompositeShape(const CompositeShape& compositeshape);
    CompositeShape(CompositeShape&& compositeshape);
    CompositeShape& operator=(const CompositeShape& compositeshape);
    CompositeShape& operator=(CompositeShape&& compositeshape);
    ShapePtr operator[](const size_t index) const;
    void addShape(const ShapePtr& shape);
    void deleteShape(const size_t index);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const double dx, const double dy) override;
    void move(const point_t& center) override;
    point_t getCenter() const override;
    size_t getSize() const;
    void printInfo() const override;
    void scale(const double coef) override;
    void rotate(const double angle) override;
    Matrix getPartition() const;
  private:
    using ShapeArrayPtr = std::unique_ptr<ShapePtr[]>;
    ShapeArrayPtr shapes_;
    size_t size_;
  };
}

#endif
