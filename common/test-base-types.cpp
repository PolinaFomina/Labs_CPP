#include <boost/test/unit_test.hpp>

#include "base-types.hpp"

BOOST_AUTO_TEST_SUITE(BaseFunctionsTest)

const double EPSILON = 0.000001;

BOOST_AUTO_TEST_CASE(RotationCheck)
{
  const double ANGLE = 90;
  fomina::point_t rotating_point1 = { 5.0, 5.0 };
  fomina::point_t rotating_point2 = { 0.0, 0.0 };
  const fomina::point_t static_point = { 0.0, 0.0 };
  fomina::details::rotatePoint(rotating_point1, static_point, ANGLE);
  BOOST_CHECK_CLOSE(rotating_point1.x, -5.0, EPSILON);
  BOOST_CHECK_CLOSE(rotating_point1.y, 5.0, EPSILON);
  fomina::details::rotatePoint(rotating_point2, static_point, ANGLE);
  BOOST_CHECK_CLOSE(rotating_point2.x, rotating_point2.x, EPSILON);
  BOOST_CHECK_CLOSE(rotating_point2.y, rotating_point2.y, EPSILON);
}

BOOST_AUTO_TEST_CASE(OverlappingCheck)
{
  const fomina::rectangle_t rectangle{ 4.0, 5.0, { 9.0, 4.5 } };
  const fomina::rectangle_t rectangle0{ 4.0, 5.0, { 9.0, 4.5 } };
  const fomina::rectangle_t rectangle1{ 4.0, 5.0, { 12.0, 4.5 } };
  const fomina::rectangle_t rectangle2{ 4.0, 5.0, { 6.0, 4.5 } };
  const fomina::rectangle_t rectangle3{ 4.0, 5.0, { 9.0, 0.0 } };
  const fomina::rectangle_t rectangle4{ 4.0, 5.0, { 9.0, 9.0 } };
  BOOST_REQUIRE_EQUAL(fomina::details::areOverlapped(rectangle, rectangle0), 1);
  BOOST_REQUIRE_EQUAL(fomina::details::areOverlapped(rectangle, rectangle1), 1);
  BOOST_REQUIRE_EQUAL(fomina::details::areOverlapped(rectangle, rectangle3), 1);
  BOOST_REQUIRE_EQUAL(fomina::details::areOverlapped(rectangle1, rectangle2), 0);
  BOOST_REQUIRE_EQUAL(fomina::details::areOverlapped(rectangle3, rectangle4), 0);
}

BOOST_AUTO_TEST_SUITE_END()
