#include "matrix.hpp"
#include <iostream>
#include <stdexcept>
#include <memory>
#include "shape.hpp"

fomina::Matrix::Matrix() :
  layersCount_(0),
  columnsCount_(0),
  shapes_(nullptr)
{
}

fomina::Matrix::Matrix(const Matrix& matrix) :
  layersCount_(0),
  columnsCount_(0),
  shapes_(nullptr)
{
  if (matrix.layersCount_)
  {
    shapes_ = std::make_unique<Shape::ShapePtr[]>(matrix.layersCount_ * matrix.columnsCount_);
    layersCount_ = matrix.layersCount_;
    columnsCount_ = matrix.columnsCount_;
    for (size_t i = 0; i < (layersCount_ * columnsCount_); i++)
    {
      shapes_[i] = matrix.shapes_[i];
    }
  }
}

fomina::Matrix::Matrix(Matrix&& matrix) :
  layersCount_(matrix.layersCount_),
  columnsCount_(matrix.columnsCount_),
  shapes_(std::move(matrix.shapes_))
{
  matrix.layersCount_ = 0;
  matrix.columnsCount_ = 0;
}

fomina::Matrix& fomina::Matrix::operator=(const Matrix& matrix)
{
  if (this != &matrix)
  {
    if (matrix.layersCount_)
    {
      shapes_ = std::make_unique<Shape::ShapePtr[]>(matrix.layersCount_ * matrix.columnsCount_);
      layersCount_ = matrix.layersCount_;
      columnsCount_ = matrix.columnsCount_;
      for (size_t i = 0; i < (layersCount_ * columnsCount_); i++)
      {
        shapes_[i] = matrix.shapes_[i];
      }
    }
    else
    {
      layersCount_ = 0;
      columnsCount_ = 0;
      shapes_ = nullptr;
    }
  }
  return *this;
}

fomina::Matrix& fomina::Matrix::operator=(Matrix&& matrix)
{
  if (this != &matrix)
  {
    if (matrix.layersCount_)
    {
      shapes_ = std::move(matrix.shapes_);
      layersCount_ = matrix.layersCount_;
      columnsCount_ = matrix.columnsCount_;
    }
    else
    {
      shapes_ = nullptr;
    }
  }
  matrix.layersCount_ = 0;
  matrix.columnsCount_ = 0;
  return *this;
}

fomina::Matrix::ConstLayer fomina::Matrix::operator[](const size_t index) const
{
  if (index >= layersCount_)
  {
    throw std::invalid_argument("Index must be in the range [0, layersCount_)");
  }

  return ConstLayer(this, index);
}

fomina::Matrix::Layer fomina::Matrix::operator[](const size_t index)
{
  if (index >= layersCount_)
  {
    throw std::invalid_argument("Index must be in the range [0, layersCount_)");
  }

  return Layer(this, index);
}

fomina::Shape::ShapePtr fomina::Matrix::ConstLayer::operator[] (const size_t index) const
{
  if (index >= getSize())
  {
    throw std::invalid_argument("Index must be in the range [0, RealColumnsCount_)");
  }

  return matrix_->shapes_[layerIndex_ * (matrix_->columnsCount_) + index];
}

size_t fomina::Matrix::ConstLayer::getSize() const
{
  size_t counter = 0;
  for (size_t i = 0; i < matrix_->columnsCount_; i++)
  {
    if (matrix_->shapes_[layerIndex_ * matrix_->columnsCount_ + i])
    {
      counter++;
    }
  }
  return counter;
}

fomina::Matrix::ConstLayer::ConstLayer(const Matrix* matrix, const size_t layerIndex) :
  layerIndex_(layerIndex),
  matrix_(matrix)
{
}

void fomina::Matrix::Layer::addShape(const Shape::ShapePtr& shape)
{
  matrix_->add(shape, layerIndex_);
}

fomina::Matrix::Layer::Layer(Matrix* matrix, const size_t layerIndex) :
  ConstLayer(matrix, layerIndex),
  matrix_(matrix)
{
}

void fomina::Matrix::addLayer()
{
  size_t counter = 0;
  Shape::ShapeArrayPtr temp = std::make_unique<Shape::ShapePtr[]>(++layersCount_ * columnsCount_);
  for (size_t i = 0; i < layersCount_ - 1; i++)
  {
    for (size_t j = 0; j < columnsCount_; j++)
    {
      temp[i * columnsCount_ + j] = shapes_[counter];
      counter++;
    }
  }
  shapes_ = std::move(temp);
}

void fomina::Matrix::addColumn()
{
  size_t counter = 0;
  Shape::ShapeArrayPtr temp = std::make_unique<Shape::ShapePtr[]>(++columnsCount_ * layersCount_);
  for (size_t i = 0; i < layersCount_; i++)
  {
    for (size_t j = 0; j < columnsCount_ - 1; j++)
    {
      temp[i * columnsCount_ + j] = shapes_[counter];
      counter++;
    }
  }
  shapes_ = std::move(temp);
}

size_t fomina::Matrix::getLayersCount() const
{
  return layersCount_;
}

void fomina::Matrix::printInfo() const
{
  std::cout << "Matrix:" << "\n";
  for (size_t i = 0; i < layersCount_; i++)
  {
    std::cout << i << " layer" << '\n';
    for (size_t j = 0; j < columnsCount_; j++)
    {
      if (shapes_[i * columnsCount_ + j])
      {
        std::cout << "Shape " << j << ":" << "\n";
        shapes_[i * columnsCount_ + j]->printInfo();
      }
    }
  }
}

void fomina::Matrix::add(const Shape::ShapePtr& shape, const size_t layerIndex)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Shape is missing");
  }

  bool isInserted = false;
  for (size_t i = 0; i < columnsCount_; i++)
  {
    if (!shapes_[(layerIndex * columnsCount_) + i])
    {
      shapes_[(layerIndex * columnsCount_) + i] = shape;
      isInserted = true;
      break;
    }
  }
  if (!isInserted)
  {
    addColumn();
    shapes_[layerIndex * columnsCount_ + columnsCount_ - 1] = shape;
  }
}
