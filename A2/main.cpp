#include <iostream>
#include <stdexcept>

#include "rectangle.hpp"
#include "circle.hpp"
#include "base-types.hpp"

int main()
{
  try
  {
    fomina::Shape* shape = nullptr;

    try
    {
      std::cout << "Rectangle" << "\n";

      fomina::point_t rectangle_center = { 1.8, 8 };
      fomina::Rectangle rectangle(8, 12, rectangle_center);
      shape = &rectangle;
      shape->printInfo();

      shape->move(3, -2);
      std::cout << "Rectangle after moving x = 3, y = -2 " << "\n";
      shape->printInfo();

      fomina::point_t point_move_rectangle = { -20, 4 };
      shape->move(point_move_rectangle);
      std::cout << "Rectangle after moving point(-20, 4) " << "\n";
      shape->printInfo();

      shape->scale(5);
      std::cout << "Rectangle after scaling with coefficient 5 " << "\n";
      shape->printInfo();
    }
    catch (const std::invalid_argument& error)
    {
      std::cerr << "Error: " << error.what();
      return 1;
    }

    try
    {
      std::cout << "Circle" << "\n";

      fomina::point_t circle_center = { 3, 10.5 };
      fomina::Circle circle(circle_center, 15);
      shape = &circle;
      shape->printInfo();

      shape->move(0, -0.5);
      std::cout << "Circle after moving x = 0, y = -0.5 " << "\n";
      shape->printInfo();

      fomina::point_t point_move_circle = { 6, -6 };
      shape->move(point_move_circle);
      std::cout << "Circle after moving point(6, -6) " << "\n";
      shape->printInfo();

      shape->scale(2);
      std::cout << "Circle after scaling with coefficient 2 " << "\n";
      shape->printInfo();
    }
    catch (const std::invalid_argument& error)
    {
      std::cerr << "Error: " << error.what();
      return 1;
    }
  }
  catch (...)
  {
    std::cerr << "An unexpected error occurred";
    return 1;
  }
  return 0;
}

