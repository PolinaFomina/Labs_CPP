#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>
#include "shape.hpp"

namespace fomina
{
  class Matrix
  {
  public:

    class ConstLayer
    {
    public:
      Shape::ShapePtr operator[](const size_t index) const;
      size_t getSize() const;
    protected:
      size_t layerIndex_;
    private:
      friend Matrix;
      const Matrix* matrix_;
      ConstLayer(const Matrix* matrix, const size_t layerIndex);
    };

    class Layer : public ConstLayer
    {
    public:
      void addShape(const Shape::ShapePtr& shape);
    private:
      friend Matrix;
      Matrix* matrix_;
      Layer(Matrix* matrix, const size_t size);
    };

    Matrix();
    Matrix(const Matrix& matrix);
    Matrix(Matrix&& martix);
    ~Matrix() = default;
    Matrix& operator=(const Matrix& matrix);
    Matrix& operator=(Matrix&& object);
    ConstLayer operator[] (const size_t index) const;
    Layer operator[] (const size_t index);
    void addLayer();
    size_t getLayersCount() const;
    void printInfo() const;
  private:
    size_t layersCount_;
    size_t columnsCount_;
    Shape::ShapeArrayPtr shapes_;
    void addColumn();
    void add(const Shape::ShapePtr& shape, const size_t layerIndex);
  };
}

#endif
