#include "splitting.hpp"
#include "matrix.hpp"
#include "base-types.hpp"

fomina::Matrix fomina::splitIntoLayers(const Shape::ShapeArrayPtr& array, const size_t size)
{
  Matrix matrix;
  for (size_t k = 0; k < size; k++)
  {
    size_t layer = 0;
    for (size_t i = 0; i < matrix.getLayersCount(); i++)
    {
      for (size_t j = 0; j < matrix[i].getSize(); j++)
      {
        if (details::areOverlapped(matrix[i][j]->getFrameRect(), array[k]->getFrameRect()))
        {
          layer = i;
          break;
        }
      }
    }
    if ((matrix.getLayersCount() == 0) || (layer == (matrix.getLayersCount() - 1)))
    {
      matrix.addLayer();
      matrix[matrix.getLayersCount() - 1].addShape(array[k]);
    }
    else
    {
      matrix[layer + 1].addShape(array[k]);
    }
  }
  return matrix;
}
