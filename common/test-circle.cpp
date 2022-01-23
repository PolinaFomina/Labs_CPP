#include <stdexcept>

#define _USE_MATH_DEFINES

#include <cmath>
#include <boost/test/unit_test.hpp>

#include "circle.hpp"
#include "base-types.hpp"

BOOST_AUTO_TEST_SUITE(CircleTest)

const double EPSILON = 0.000001;
const double RADIUS = 10.0;
const fomina::point_t CENTER = { 4.0, 6.5 };
const double DX = 5.0;
const double DY = 5.0;
const fomina::point_t MOVEPOINT = { 7.0, 7.0 };
const double COEF = 2.0;
const double ANGLE = 90;

BOOST_AUTO_TEST_CASE(CircleGettersCheck)
{
  fomina::Circle circ(CENTER, RADIUS);
  BOOST_CHECK_CLOSE(circ.getCenter().x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(circ.getCenter().y, CENTER.y, EPSILON);
  BOOST_CHECK_CLOSE(circ.getRadius(), RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(circ.getArea(), M_PI * RADIUS * RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(circ.getFrameRect().width, 2 * RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(circ.getFrameRect().height, 2 * RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(circ.getFrameRect().pos.x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(circ.getFrameRect().pos.y, CENTER.y, EPSILON);
}

BOOST_AUTO_TEST_CASE(CircleAfterMovingOnAxes)
{
  fomina::Circle circ(CENTER, RADIUS);
  circ.move(DX, DY);
  BOOST_CHECK_CLOSE(circ.getCenter().x, CENTER.x + DX, EPSILON);
  BOOST_CHECK_CLOSE(circ.getCenter().y, CENTER.y + DY, EPSILON);
  BOOST_CHECK_CLOSE(circ.getRadius(), RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(circ.getArea(), M_PI * RADIUS * RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(circ.getFrameRect().width, 2 * RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(circ.getFrameRect().height, 2 * RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(circ.getFrameRect().pos.x, CENTER.x + DX, EPSILON);
  BOOST_CHECK_CLOSE(circ.getFrameRect().pos.y, CENTER.y + DY, EPSILON);
}

BOOST_AUTO_TEST_CASE(CircleAfterMovingInPoint)
{
  fomina::Circle circ(CENTER, RADIUS);
  circ.move(MOVEPOINT);
  BOOST_CHECK_CLOSE(circ.getCenter().x, MOVEPOINT.x, EPSILON);
  BOOST_CHECK_CLOSE(circ.getCenter().y, MOVEPOINT.y, EPSILON);
  BOOST_CHECK_CLOSE(circ.getRadius(), RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(circ.getArea(), M_PI * RADIUS * RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(circ.getFrameRect().width, 2 * RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(circ.getFrameRect().height, 2 * RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(circ.getFrameRect().pos.x, MOVEPOINT.x, EPSILON);
  BOOST_CHECK_CLOSE(circ.getFrameRect().pos.y, MOVEPOINT.y, EPSILON);
}

BOOST_AUTO_TEST_CASE(CircleAfterScaling)
{
  fomina::Circle circ(CENTER, RADIUS);
  circ.scale(COEF);
  BOOST_CHECK_CLOSE(circ.getCenter().x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(circ.getCenter().y, CENTER.y, EPSILON);
  BOOST_CHECK_CLOSE(circ.getRadius(), RADIUS * COEF, EPSILON);
  BOOST_CHECK_CLOSE(circ.getArea(), M_PI * RADIUS * RADIUS * COEF * COEF, EPSILON);
  BOOST_CHECK_CLOSE(circ.getFrameRect().width, 2 * RADIUS * COEF, EPSILON);
  BOOST_CHECK_CLOSE(circ.getFrameRect().height, 2 * RADIUS * COEF, EPSILON);
  BOOST_CHECK_CLOSE(circ.getFrameRect().pos.x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(circ.getFrameRect().pos.y, CENTER.y, EPSILON);
}

BOOST_AUTO_TEST_CASE(CircleAfterRotation)
{
  fomina::Circle circ(CENTER, RADIUS);
  circ.rotate(ANGLE);
  BOOST_CHECK_CLOSE(circ.getCenter().x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(circ.getCenter().y, CENTER.y, EPSILON);
  BOOST_CHECK_CLOSE(circ.getRadius(), RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(circ.getArea(), M_PI * RADIUS * RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(circ.getFrameRect().width, 2 * RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(circ.getFrameRect().height, 2 * RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(circ.getFrameRect().pos.x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(circ.getFrameRect().pos.y, CENTER.y, EPSILON);
}

BOOST_AUTO_TEST_CASE(CircleInvalidRadius)
{
  BOOST_CHECK_THROW(fomina::Circle circ(CENTER, -RADIUS), std::invalid_argument);
  BOOST_CHECK_THROW(fomina::Circle circ(CENTER, 0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(CircleInvalidCoef)
{
  fomina::Circle circ(CENTER, RADIUS);
  BOOST_CHECK_THROW(circ.scale(-COEF), std::invalid_argument);
  BOOST_CHECK_THROW(circ.scale(0), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
