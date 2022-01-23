#include <stdexcept>
#include <memory>
#include <boost/test/unit_test.hpp>

#include "matrix.hpp"
#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "shape.hpp"
#include "base-types.hpp"

BOOST_AUTO_TEST_SUITE(MatrixTest)

const double RADIUS_C = 20.0;
const double WIDTH_R = 2.0;
const double HEIGHT_R = 6.0;
const fomina::point_t CENTER_R = { 6.0, 4.2 };
const fomina::point_t CENTER_R1 = { 6.2, 4.0 };
const fomina::point_t CENTER_C = { 6.2, 4.0 };

struct Fixture
{
  Fixture() :
    rectangle(std::make_shared<fomina::Rectangle>(fomina::Rectangle(WIDTH_R, HEIGHT_R, CENTER_R))),
    rectangle1(std::make_shared<fomina::Rectangle>(fomina::Rectangle(WIDTH_R, HEIGHT_R, CENTER_R1))),
    circle(std::make_shared<fomina::Circle>(fomina::Circle(CENTER_C, RADIUS_C)))
  {
    matrix.addLayer();
    matrix[0].addShape(rectangle);
    matrix[0].addShape(circle);
    matrix.addLayer();
    matrix[1].addShape(rectangle1);
  }
  fomina::Shape::ShapePtr rectangle;
  fomina::Shape::ShapePtr rectangle1;
  fomina::Shape::ShapePtr circle;
  fomina::Matrix matrix;
};

BOOST_AUTO_TEST_CASE(MatrixEmptyCheck)
{
  fomina::Matrix matrix;
  BOOST_CHECK(matrix.getLayersCount() == 0);
}

BOOST_AUTO_TEST_CASE(MatrixAddLayer)
{
  fomina::Matrix matrix;
  matrix.addLayer();
  BOOST_CHECK(matrix.getLayersCount() == 1);
  BOOST_CHECK(matrix[0].getSize() == 0);
}

BOOST_AUTO_TEST_CASE(MatrixAddShape)
{
  fomina::Shape::ShapePtr rectangle = std::make_shared<fomina::Rectangle>(fomina::Rectangle(WIDTH_R, HEIGHT_R, CENTER_R));
  fomina::Shape::ShapePtr circle = std::make_shared<fomina::Circle>(fomina::Circle(CENTER_C, RADIUS_C));
  fomina::Matrix matrix;
  matrix.addLayer();
  matrix[0].addShape(rectangle);
  BOOST_CHECK(matrix.getLayersCount() == 1);
  BOOST_CHECK(matrix[0].getSize() == 1);
  BOOST_CHECK(matrix[0][0] == rectangle);
  matrix[0].addShape(circle);
  BOOST_CHECK(matrix.getLayersCount() == 1);
  BOOST_CHECK(matrix[0].getSize() == 2);
  BOOST_CHECK(matrix[0][1] == circle);
}

BOOST_FIXTURE_TEST_CASE(MatrixCopyConstructor, Fixture)
{
  fomina::Matrix matrix1(matrix);
  BOOST_CHECK(matrix1[0][0] == matrix[0][0]);
  BOOST_CHECK(matrix1[0][1] == matrix[0][1]);
  BOOST_CHECK(matrix1[1][0] == matrix[1][0]);
  BOOST_CHECK(matrix1.getLayersCount() == matrix.getLayersCount());
  BOOST_CHECK(matrix1[0].getSize() == matrix[0].getSize());
  BOOST_CHECK(matrix1[1].getSize() == matrix[1].getSize());
}

BOOST_FIXTURE_TEST_CASE(MatrixCopyOperator, Fixture)
{
  fomina::Matrix matrix1 = matrix;
  BOOST_CHECK(matrix1[0][0] == matrix[0][0]);
  BOOST_CHECK(matrix1[0][1] == matrix[0][1]);
  BOOST_CHECK(matrix1[1][0] == matrix[1][0]);
  BOOST_CHECK(matrix1.getLayersCount() == matrix.getLayersCount());
  BOOST_CHECK(matrix1[0].getSize() == matrix[0].getSize());
  BOOST_CHECK(matrix1[1].getSize() == matrix[1].getSize());
}

BOOST_AUTO_TEST_CASE(MatrixInvalidShape)
{
  fomina::Matrix matrix;
  matrix.addLayer();
  BOOST_CHECK_THROW(matrix[0].addShape(nullptr), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(MatrixInvalidIndex)
{
  fomina::Matrix matrix;
  BOOST_CHECK_THROW(matrix[0], std::invalid_argument);
  BOOST_CHECK_THROW(matrix[0][0], std::invalid_argument);
  BOOST_CHECK_THROW(matrix[-1], std::invalid_argument);
  BOOST_CHECK_THROW(matrix[0][-1], std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
