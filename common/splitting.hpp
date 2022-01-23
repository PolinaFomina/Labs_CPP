#ifndef SPLITTING_HPP
#define SPLITTING_HPP

#include "shape.hpp"

namespace fomina
{
  class Matrix;
  fomina::Matrix splitIntoLayers(const Shape::ShapeArrayPtr& array, const size_t size);
}

#endif
