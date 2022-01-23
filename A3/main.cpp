#include <iostream>
#include <memory>
#include <stdexcept>
#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "shape.hpp"
#include "base-types.hpp"

int main()
{
  try
  {
    fomina::Shape::ShapePtr rectangle = std::make_shared<fomina::Rectangle>(fomina::Rectangle(8, 12, fomina::point_t{ 1.8, 8 }));
    fomina::Shape::ShapePtr circle = std::make_shared<fomina::Circle>(fomina::Circle(fomina::point_t{ 3, 10.5 }, 15));

    fomina::CompositeShape composite_shape1;
    try
    {
      composite_shape1.addShape(rectangle);
      composite_shape1.addShape(circle);
    }
    catch (const std::invalid_argument& error)
    {
      std::cerr << "Error: " << error.what();
      return 1;
    }
    composite_shape1.printInfo();

    composite_shape1.move(0, -0.5);
    std::cout << "composite_shape1 after moving x = 0, y = -0.5 " << "\n";
    composite_shape1.printInfo();

    fomina::point_t point_move = { 6, -6 };
    composite_shape1.move(point_move);
    std::cout << "composite_shape1 after moving point(6, -6) " << "\n";
    composite_shape1.printInfo();

    try
    {
      composite_shape1.scale(2);
    }
    catch (const std::invalid_argument& error)
    {
      std::cerr << "Error: " << error.what();
      return 1;
    }
    std::cout << "composite_shape1 after scaling with coefficient 2 " << "\n";
    composite_shape1.printInfo();

    try
    {
      composite_shape1.deleteShape(1);
    }
    catch (const std::invalid_argument& error)
    {
      std::cerr << "Error: " << error.what();
      return 1;
    }
    std::cout << "composite_shape1 after deleting second shape" << "\n";
    composite_shape1.printInfo();

    fomina::CompositeShape composite_shape2(composite_shape1);
    std::cout << "composite_shape2 - copy of composite_shape1" << "\n";
    composite_shape2.printInfo();
  }
  catch (...)
  {
    std::cerr << "An unexpected error occurred";
    return 1;
  }
  return 0;
}
