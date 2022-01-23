#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

int main()
{
  std::cout << "Rectangle" << "\n";

  point_t rectangle_center;
  rectangle_center.x = 1.8;
  rectangle_center.y = 8;

  Rectangle rectangle(8, 12, rectangle_center);
  Shape* shape = &rectangle;
  shape->printInfo();

  rectangle.move(3, -2);
  std::cout << "Rectangle after moving x = 3, y = -2 " << "\n";
  shape->printInfo();

  point_t point_move_rectangle;
  point_move_rectangle.x = -20;
  point_move_rectangle.y = 4;
  rectangle.move(point_move_rectangle);
  std::cout << "Rectangle after moving point(-20, 4) " << "\n";
  shape->printInfo();

  std::cout << "Circle" << "\n";

  point_t circle_center;
  circle_center.x = 3;
  circle_center.y = 10.5;

  Circle circle(circle_center, 15);
  shape = &circle;
  shape->printInfo();

  circle.move(0, -0.5);
  std::cout << "Circle after moving x = 0, y = -0.5 " << "\n";
  shape->printInfo();

  point_t point_move_circle;
  point_move_circle.x = 6;
  point_move_circle.y = -6;
  circle.move(point_move_circle);
  std::cout << "Circle after moving point(6, -6) " << "\n";
  shape->printInfo();

  return 0;
}
