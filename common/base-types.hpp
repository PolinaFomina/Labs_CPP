#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

namespace fomina
{
  struct point_t
  {
    double x;
    double y;
  };

  struct rectangle_t
  {
    double width;
    double height;
    point_t pos;
  };

  namespace details
  {
    void rotatePoint(point_t& rotatingPoint, const point_t& staticPoint, const double angle);
    bool areOverlapped(const rectangle_t& firstRectangle, const rectangle_t& secondRectangle);
  }
}

#endif
