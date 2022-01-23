#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include "rectangle.hpp"
#include "base-types.hpp"


BOOST_AUTO_TEST_SUITE(RectangleTest)

const double EPSILON = 0.000001;
const double WIDTH = 10.0;
const double HEIGHT = 5.0;
const double AREA = 50.0;
const fomina::point_t CENTER = { 4.2, 6.0 };
const fomina::point_t CORNERS[4] = { { -0.8, 3.5 }, { -0.8, 8.5 }, { 9.2, 8.5 }, { 9.2, 3.5 } };
const double DX = 7.0;
const double DY = 7.0;
const fomina::point_t MOVEPOINT = { 6.0, 6.0 };
const double COEF = 3.0;
const double ANGLE = 90;

BOOST_AUTO_TEST_CASE(RectangleGettersCheck)
{
  fomina::Rectangle rect(WIDTH, HEIGHT, CENTER);
  BOOST_CHECK_CLOSE(rect.getWidth(), WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(rect.getHeight(), HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(rect.getCenter().x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(rect.getCenter().y, CENTER.y, EPSILON);
  BOOST_CHECK_CLOSE(rect.getArea(), AREA, EPSILON);
  BOOST_CHECK_CLOSE(rect.getFrameRect().width, rect.getWidth(), EPSILON);
  BOOST_CHECK_CLOSE(rect.getFrameRect().height, rect.getHeight(), EPSILON);
  BOOST_CHECK_CLOSE(rect.getFrameRect().pos.x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(rect.getFrameRect().pos.y, CENTER.y, EPSILON);
}

BOOST_AUTO_TEST_CASE(RectangleAfterMovingOnAxes)
{
  fomina::Rectangle rect(WIDTH, HEIGHT, CENTER);
  rect.move(DX, DY);
  BOOST_CHECK_CLOSE(rect.getWidth(), WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(rect.getHeight(), HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(rect.getCenter().x, CENTER.x + DX, EPSILON);
  BOOST_CHECK_CLOSE(rect.getCenter().y, CENTER.y + DY, EPSILON);
  BOOST_CHECK_CLOSE(rect.getArea(), AREA, EPSILON);
  BOOST_CHECK_CLOSE(rect.getFrameRect().width, rect.getWidth(), EPSILON);
  BOOST_CHECK_CLOSE(rect.getFrameRect().height, rect.getHeight(), EPSILON);
  BOOST_CHECK_CLOSE(rect.getFrameRect().pos.x, CENTER.x + DX, EPSILON);
  BOOST_CHECK_CLOSE(rect.getFrameRect().pos.y, CENTER.y + DY, EPSILON);
}

BOOST_AUTO_TEST_CASE(RectangleAfterMovingInPoint)
{
  fomina::Rectangle rect(WIDTH, HEIGHT, CENTER);
  rect.move(MOVEPOINT);
  BOOST_CHECK_CLOSE(rect.getWidth(), WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(rect.getHeight(), HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(rect.getCenter().x, MOVEPOINT.x, EPSILON);
  BOOST_CHECK_CLOSE(rect.getCenter().y, MOVEPOINT.y, EPSILON);
  BOOST_CHECK_CLOSE(rect.getArea(), AREA, EPSILON);
  BOOST_CHECK_CLOSE(rect.getFrameRect().width, rect.getWidth(), EPSILON);
  BOOST_CHECK_CLOSE(rect.getFrameRect().height, rect.getHeight(), EPSILON);
  BOOST_CHECK_CLOSE(rect.getFrameRect().pos.x, MOVEPOINT.x, EPSILON);
  BOOST_CHECK_CLOSE(rect.getFrameRect().pos.y, MOVEPOINT.y, EPSILON);
}

BOOST_AUTO_TEST_CASE(RectangleAfterScaling)
{
  fomina::Rectangle rect(WIDTH, HEIGHT, CENTER);
  rect.scale(COEF);
  BOOST_CHECK_CLOSE(rect.getWidth(), WIDTH * COEF, EPSILON);
  BOOST_CHECK_CLOSE(rect.getHeight(), HEIGHT * COEF, EPSILON);
  BOOST_CHECK_CLOSE(rect.getCenter().x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(rect.getCenter().y, CENTER.y, EPSILON);
  BOOST_CHECK_CLOSE(rect.getArea(), AREA * COEF * COEF, EPSILON);
  BOOST_CHECK_CLOSE(rect.getFrameRect().height, rect.getHeight(), EPSILON);
  BOOST_CHECK_CLOSE(rect.getFrameRect().width, rect.getWidth(), EPSILON);
  BOOST_CHECK_CLOSE(rect.getFrameRect().pos.x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(rect.getFrameRect().pos.y, CENTER.y, EPSILON);
}

BOOST_AUTO_TEST_CASE(RectangleAfterRotation)
{
  fomina::Rectangle rect(WIDTH, HEIGHT, CENTER);
  rect.rotate(ANGLE);
  BOOST_CHECK_CLOSE(rect.getWidth(), WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(rect.getHeight(), HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(rect.getCenter().x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(rect.getCenter().y, CENTER.y, EPSILON);
  BOOST_CHECK_CLOSE(rect.getArea(), AREA, EPSILON);
  BOOST_CHECK_CLOSE(rect.getFrameRect().height, rect.getWidth(), EPSILON);
  BOOST_CHECK_CLOSE(rect.getFrameRect().width, rect.getHeight(), EPSILON);
  BOOST_CHECK_CLOSE(rect.getFrameRect().pos.x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(rect.getFrameRect().pos.y, CENTER.y, EPSILON);
}

BOOST_AUTO_TEST_CASE(RectangleInvalidWidth)
{
  BOOST_CHECK_THROW(fomina::Rectangle rect(-WIDTH, HEIGHT, CENTER), std::invalid_argument);
  BOOST_CHECK_THROW(fomina::Rectangle rect(0, HEIGHT, CENTER), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(RectangleInvalidHeight)
{
  BOOST_CHECK_THROW(fomina::Rectangle rect(WIDTH, -HEIGHT, CENTER), std::invalid_argument);
  BOOST_CHECK_THROW(fomina::Rectangle rect(WIDTH, 0, CENTER), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(RectangleInvalidCoef)
{
  fomina::Rectangle rect(WIDTH, HEIGHT, CENTER);
  BOOST_CHECK_THROW(rect.scale(-COEF), std::invalid_argument);
  BOOST_CHECK_THROW(rect.scale(0), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
