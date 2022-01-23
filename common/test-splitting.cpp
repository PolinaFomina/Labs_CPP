#include <memory>
#include <boost/test/unit_test.hpp>

#include "splitting.hpp"
#include "matrix.hpp"
#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "shape.hpp"
#include "base-types.hpp"

BOOST_AUTO_TEST_SUITE(SplittingTest)

const double RADIUS_C1 = 2.0;
const double RADIUS_C2 = 1.0;
const double WIDTH_R = 4.0;
const double HEIGHT_R = 5.0;
const double WIDTH_R3 = 7.0;
const double HEIGHT_R3 = 4.0;
const fomina::point_t CENTER_R1 = { 9.0, 4.5 };
const fomina::point_t CENTER_R2 = { 7.0, 8.5 };
const fomina::point_t CENTER_R3 = { 5.5, 3.0 };
const fomina::point_t CENTER_C1 = { 4.0, 9.0 };
const fomina::point_t CENTER_C2 = { 2.0, 5.0 };

BOOST_AUTO_TEST_CASE(SplittingCheck)
{
  fomina::CompositeShape composite_shape;
  fomina::Shape::ShapePtr rectangle1 = std::make_shared<fomina::Rectangle>(fomina::Rectangle(WIDTH_R, HEIGHT_R, CENTER_R1));
  fomina::Shape::ShapePtr rectangle2 = std::make_shared<fomina::Rectangle>(fomina::Rectangle(WIDTH_R, HEIGHT_R, CENTER_R2));
  composite_shape.addShape(rectangle1);
  composite_shape.addShape(rectangle2);
  fomina::Shape::ShapePtr composite_shape2 = std::make_shared<fomina::CompositeShape>(composite_shape);

  fomina::Shape::ShapeArrayPtr array = std::make_unique<fomina::Shape::ShapePtr[]>(4);
  fomina::Shape::ShapePtr rectangle3 = std::make_shared<fomina::Rectangle>(fomina::Rectangle(WIDTH_R3, HEIGHT_R3, CENTER_R3));
  fomina::Shape::ShapePtr circle1 = std::make_shared<fomina::Circle>(fomina::Circle(CENTER_C1, RADIUS_C1));
  fomina::Shape::ShapePtr circle2 = std::make_shared<fomina::Circle>(fomina::Circle(CENTER_C2, RADIUS_C2));

  array[0] = composite_shape2;
  array[1] = rectangle3;
  array[2] = circle1;
  array[3] = circle2;

  fomina::Matrix matrix;

  matrix = splitIntoLayers(array, 4);
  BOOST_CHECK(matrix[0][0] == composite_shape2);
  BOOST_CHECK(matrix[1][0] == rectangle3);
  BOOST_CHECK(matrix[1][1] == circle1);
  BOOST_CHECK(matrix[2][0] == circle2);
}

BOOST_AUTO_TEST_SUITE_END()
