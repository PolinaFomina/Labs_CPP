#include <iostream>
#include <memory>
#include <stdexcept>
#include "splitting.hpp"
#include "matrix.hpp"
#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "shape.hpp"
#include "base-types.hpp"

int main()
{
  try
  {
    fomina::Shape::ShapePtr rectangle1 = std::make_shared<fomina::Rectangle>(fomina::Rectangle(8, 12, fomina::point_t{ 1.8, 8 }));
    fomina::Shape::ShapePtr circle1 = std::make_shared<fomina::Circle>(fomina::Circle(fomina::point_t{ 3, 10.5 }, 15));
    rectangle1->printInfo();
    circle1->printInfo();

    try
    {
      rectangle1->rotate(30);
      circle1->rotate(45);
    }
    catch (const std::invalid_argument& error)
    {
      std::cerr << "Error: " << error.what();
      return 1;
    }
    std::cout << "rectangle1 after 30 degree rotation" << "\n";
    rectangle1->printInfo();
    std::cout << "circle1 after 45 degree rotation" << "\n";
    circle1->printInfo();

    fomina::CompositeShape composite_shape1;
    try
    {
      composite_shape1.addShape(rectangle1);
      composite_shape1.addShape(circle1);
    }
    catch (const std::invalid_argument& error)
    {
      std::cerr << "Error: " << error.what();
      return 1;
    }
    composite_shape1.printInfo();

    try
    {
      composite_shape1.rotate(85);
    }
    catch (const std::invalid_argument& error)
    {
      std::cerr << "Error: " << error.what();
      return 1;
    }
    std::cout << "composite_shape1 after 85 degree rotation" << "\n";
    composite_shape1.printInfo();

    fomina::Shape::ShapePtr rectangle2 = std::make_shared<fomina::Rectangle>(fomina::Rectangle(5, 3, fomina::point_t{ 0, 2 }));
    fomina::Shape::ShapePtr circle2 = std::make_shared<fomina::Circle>(fomina::Circle(fomina::point_t{ 7, 4 }, 2));
    fomina::Shape::ShapePtr rectangle3 = std::make_shared<fomina::Rectangle>(fomina::Rectangle(11, 32, fomina::point_t{ -1, 3 }));
    fomina::Shape::ShapePtr circle3 = std::make_shared<fomina::Circle>(fomina::Circle(fomina::point_t{ 2, 0 }, 4.8));
    fomina::Shape::ShapePtr rectangle4 = std::make_shared<fomina::Rectangle>(fomina::Rectangle(16, 5, fomina::point_t{ 16, 5 }));
    fomina::Shape::ShapePtr circle4 = std::make_shared<fomina::Circle>(fomina::Circle(fomina::point_t{ 5, 0 }, 4.8));
    fomina::Shape::ShapePtr rectangle5 = std::make_shared<fomina::Rectangle>(fomina::Rectangle(5, 5, fomina::point_t{ 121, 114 }));
    fomina::Shape::ShapePtr composite_shape2 = std::make_shared<fomina::CompositeShape>(composite_shape1);

    fomina::CompositeShape composite_shape;
    try
    {
      composite_shape.addShape(composite_shape2);
      composite_shape.addShape(rectangle2);
      composite_shape.addShape(circle2);
      composite_shape.addShape(rectangle3);
      composite_shape.addShape(circle3);
      composite_shape.addShape(rectangle4);
      composite_shape.addShape(circle4);
      composite_shape.addShape(rectangle5);
    }
    catch (const std::invalid_argument& error)
    {
      std::cerr << "Error: " << error.what();
      return 1;
    }
    composite_shape.printInfo();

    fomina::Matrix matrix = composite_shape.getPartition();
    std::cout << "Matrix, which is the result of the partition of the composite_shape" << "\n";
    matrix.printInfo();

    fomina::Shape::ShapePtr circle5 = std::make_shared<fomina::Circle>(fomina::Circle(fomina::point_t{ 5, 11 }, 8.1));
    try
    {
      matrix[1].addShape(circle5);
    }
    catch (const std::invalid_argument& error)
    {
      std::cerr << "Error: " << error.what();
      return 1;
    }
    std::cout << "Matrix after adding circle5 to first layer" << "\n";
    matrix.printInfo();
  }
  catch (...)
  {
    std::cerr << "An unexpected error occurred";
    return 1;
  }
  return 0;
}
