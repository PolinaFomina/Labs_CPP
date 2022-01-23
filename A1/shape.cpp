#include "shape.hpp"
#include <iostream>

void Shape::printInfo() const
{
  std::cout << "Shape's area: " << getArea() << "\n"
      << "Shape's center: " << "(" << getCenter().x << ", " << getCenter().y << ")" << "\n";
  std::cout << "Framerect's width: " << getFrameRect().width << "\n"
      << "Framerect's height: " << getFrameRect().height << "\n"
      << "Framerect's center: " << "(" << getFrameRect().pos.x << ", "
      << getFrameRect().pos.y << ")" << "\n" << "\n";
}
