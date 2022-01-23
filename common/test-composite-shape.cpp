#include <stdexcept>

#define _USE_MATH_DEFINES

#include <cmath>
#include <boost/test/unit_test.hpp>
#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "shape.hpp"
#include "base-types.hpp"

BOOST_AUTO_TEST_SUITE(CompositeShapeTest)

const double EPSILON = 0.000001;
const double AREA = 12.0 + M_PI * 400;
const double WIDTH = 40.0;
const double HEIGHT = 40.0;
fomina::point_t CENTER = { 6.2, 4.0 };
const double AREA1 = 24.0 + M_PI * 400;
const double DX = 7.0;
const double DY = 7.0;
const fomina::point_t MOVEPOINT = { 6.6, 4.0 };
const double COEF = 4.0;
const double ANGLE = 90;

const double RADIUS_C = 20.0;
const double WIDTH_R = 2.0;
const double HEIGHT_R= 6.0;
const fomina::point_t CENTER_R = { 6.0, 4.2 };
const fomina::point_t CENTER_R1 = { 6.2, 4.0 };
const fomina::point_t CENTER_C = { 6.2, 4.0 };

BOOST_AUTO_TEST_CASE(CompositeShapeEmptyCheck)
{
  fomina::CompositeShape composite_shape;
  BOOST_CHECK(composite_shape.getArea() == 0.0);
  BOOST_CHECK(composite_shape.getFrameRect().width == 0.0);
  BOOST_CHECK(composite_shape.getFrameRect().height == 0.0);
  BOOST_CHECK(composite_shape.getFrameRect().pos.x == 0.0);
  BOOST_CHECK(composite_shape.getFrameRect().pos.y == 0.0);
  BOOST_CHECK(composite_shape.getCenter().x == 0.0);
  BOOST_CHECK(composite_shape.getCenter().y == 0.0);
  BOOST_CHECK(composite_shape.getSize() == 0);
}

BOOST_AUTO_TEST_CASE(CompositeShapeAddShape)
{
  fomina::CompositeShape composite_shape;
  fomina::Shape::ShapePtr rectangle = std::make_shared<fomina::Rectangle>(fomina::Rectangle(WIDTH_R, HEIGHT_R, CENTER_R));
  fomina::Shape::ShapePtr circle = std::make_shared<fomina::Circle>(fomina::Circle(CENTER_C, RADIUS_C));
  composite_shape.addShape(rectangle);
  composite_shape.addShape(circle);
  BOOST_CHECK(composite_shape[0] == rectangle);
  BOOST_CHECK(composite_shape[1] == circle);
  BOOST_CHECK_CLOSE(composite_shape.getArea(), AREA, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().width, WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().height, HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.y, CENTER.y, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getCenter().x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getCenter().y, CENTER.y, EPSILON);
  BOOST_CHECK(composite_shape.getSize() == 2);

  fomina::Shape::ShapePtr composite_shape2 = std::make_shared<fomina::CompositeShape>(composite_shape);
  fomina::Shape::ShapePtr rectangle1 = std::make_shared<fomina::Rectangle>(fomina::Rectangle(WIDTH_R, HEIGHT_R, CENTER_R1));
  fomina::CompositeShape composite_shape1;
  composite_shape1.addShape(composite_shape2);
  composite_shape1.addShape(rectangle1);
  BOOST_CHECK(composite_shape1[0] == composite_shape2);
  BOOST_CHECK(composite_shape1[1] == rectangle1);
  BOOST_CHECK_CLOSE(composite_shape1.getArea(), AREA1, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getFrameRect().width, WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getFrameRect().height, HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getFrameRect().pos.x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getFrameRect().pos.y, CENTER.y, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getCenter().x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getCenter().y, CENTER.y, EPSILON);
  BOOST_CHECK(composite_shape1.getSize() == 2);
}

BOOST_AUTO_TEST_CASE(CompositeShapeDeleteShape)
{
  fomina::CompositeShape composite_shape;
  fomina::Shape::ShapePtr rectangle = std::make_shared<fomina::Rectangle>(fomina::Rectangle(WIDTH_R, HEIGHT_R, CENTER_R));
  fomina::Shape::ShapePtr circle = std::make_shared<fomina::Circle>(fomina::Circle(CENTER_C, RADIUS_C));
  composite_shape.addShape(rectangle);
  composite_shape.addShape(circle);
  composite_shape.deleteShape(0);
  BOOST_CHECK(composite_shape[0] == circle);
  BOOST_CHECK_CLOSE(composite_shape.getArea(), AREA - WIDTH_R * HEIGHT_R, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().width, 2 * RADIUS_C, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().height, 2 * RADIUS_C, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.x, CENTER_C.x, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.y, CENTER_C.y, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getCenter().x, CENTER_C.x, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getCenter().y, CENTER_C.y, EPSILON);
  BOOST_CHECK(composite_shape.getSize() == 1);

  fomina::Shape::ShapePtr composite_shape2 = std::make_shared<fomina::CompositeShape>(composite_shape);
  fomina::Shape::ShapePtr rectangle1 = std::make_shared<fomina::Rectangle>(fomina::Rectangle(WIDTH_R, HEIGHT_R, CENTER_R1));
  fomina::CompositeShape composite_shape1;
  composite_shape1.addShape(composite_shape2);
  composite_shape1.addShape(rectangle1);
  composite_shape1.deleteShape(1);
  BOOST_CHECK(composite_shape1[0] == composite_shape2);
  BOOST_CHECK_CLOSE(composite_shape1.getArea(), AREA1 - 2 * WIDTH_R * HEIGHT_R, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getFrameRect().width, WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getFrameRect().height, HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getFrameRect().pos.x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getFrameRect().pos.y, CENTER.y, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getCenter().x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getCenter().y, CENTER.y, EPSILON);
  BOOST_CHECK(composite_shape1.getSize() == 1);
}

BOOST_AUTO_TEST_CASE(CompositeShapeAfterScaling)
{
  fomina::CompositeShape composite_shape;
  fomina::Shape::ShapePtr rectangle = std::make_shared<fomina::Rectangle>(fomina::Rectangle(WIDTH_R, HEIGHT_R, CENTER_R));
  fomina::Shape::ShapePtr circle = std::make_shared<fomina::Circle>(fomina::Circle(CENTER_C, RADIUS_C));
  composite_shape.addShape(rectangle);
  composite_shape.addShape(circle);
  composite_shape.scale(COEF);
  BOOST_CHECK_CLOSE(composite_shape.getArea(), AREA * COEF * COEF, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().width, WIDTH * COEF, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().height, HEIGHT * COEF, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.y, CENTER.y, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getCenter().x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getCenter().y, CENTER.y, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape[0]->getCenter().x, CENTER.x + COEF * (CENTER_R.x - CENTER.x), EPSILON);
  BOOST_CHECK_CLOSE(composite_shape[0]->getCenter().y, CENTER.y + COEF * (CENTER_R.y - CENTER.y), EPSILON);
  BOOST_CHECK_CLOSE(composite_shape[1]->getCenter().x, CENTER.x + COEF * (CENTER_C.x - CENTER.x), EPSILON);
  BOOST_CHECK_CLOSE(composite_shape[1]->getCenter().y, CENTER.y + COEF * (CENTER_C.y - CENTER.y), EPSILON);
  BOOST_CHECK(composite_shape.getSize() == 2);

  fomina::CompositeShape composite_shape3;
  fomina::Shape::ShapePtr rectangle1 = std::make_shared<fomina::Rectangle>(fomina::Rectangle(WIDTH_R, HEIGHT_R, CENTER_R));
  fomina::Shape::ShapePtr circle1 = std::make_shared<fomina::Circle>(fomina::Circle(CENTER_C, RADIUS_C));
  composite_shape3.addShape(rectangle1);
  composite_shape3.addShape(circle1);
  fomina::Shape::ShapePtr composite_shape2 = std::make_shared<fomina::CompositeShape>(composite_shape3);
  fomina::Shape::ShapePtr rectangle2 = std::make_shared<fomina::Rectangle>(fomina::Rectangle(WIDTH_R, HEIGHT_R, CENTER_R1));
  fomina::CompositeShape composite_shape1;
  composite_shape1.addShape(composite_shape2);
  composite_shape1.addShape(rectangle2);
  composite_shape1.scale(COEF);
  BOOST_CHECK_CLOSE(composite_shape1.getArea(), AREA1 * COEF * COEF, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getFrameRect().width, WIDTH * COEF, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getFrameRect().height, HEIGHT * COEF, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getFrameRect().pos.x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getFrameRect().pos.y, CENTER.y, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getCenter().x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getCenter().y, CENTER.y, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1[0]->getCenter().x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1[0]->getCenter().y, CENTER.y, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1[1]->getCenter().x, CENTER.x + COEF * (CENTER_R1.x - CENTER.x), EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1[1]->getCenter().y, CENTER.y + COEF * (CENTER_R1.y - CENTER.y), EPSILON);
  BOOST_CHECK(composite_shape1.getSize() == 2);
}

BOOST_AUTO_TEST_CASE(CompositeShapeAfterRotation)
{
  fomina::CompositeShape composite_shape;
  fomina::Shape::ShapePtr rectangle = std::make_shared<fomina::Rectangle>(fomina::Rectangle(WIDTH_R, HEIGHT_R, CENTER_R));
  fomina::Shape::ShapePtr circle = std::make_shared<fomina::Circle>(fomina::Circle(CENTER_C, RADIUS_C));
  composite_shape.addShape(rectangle);
  composite_shape.addShape(circle);
  fomina::point_t NEWCENTER_R = composite_shape[0]->getCenter();
  fomina::point_t NEWCENTER_C = composite_shape[1]->getCenter();
  const fomina::point_t NEWCENTER_ = composite_shape.getCenter();
  fomina::details::rotatePoint(NEWCENTER_R, NEWCENTER_, ANGLE);
  fomina::details::rotatePoint(NEWCENTER_C, NEWCENTER_, ANGLE);
  composite_shape.rotate(ANGLE);
  BOOST_CHECK_CLOSE(composite_shape.getArea(), AREA, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().width, WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().height, HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.y, CENTER.y, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getCenter().x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getCenter().y, CENTER.y, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape[0]->getCenter().x, NEWCENTER_R.x, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape[0]->getCenter().y, NEWCENTER_R.y, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape[1]->getCenter().x, NEWCENTER_C.x, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape[1]->getCenter().y, NEWCENTER_C.y, EPSILON);
  BOOST_CHECK(composite_shape.getSize() == 2);

  fomina::CompositeShape composite_shape3;
  fomina::Shape::ShapePtr rectangle1 = std::make_shared<fomina::Rectangle>(fomina::Rectangle(WIDTH_R, HEIGHT_R, CENTER_R));
  fomina::Shape::ShapePtr circle1 = std::make_shared<fomina::Circle>(fomina::Circle(CENTER_C, RADIUS_C));
  composite_shape3.addShape(rectangle1);
  composite_shape3.addShape(circle1);
  fomina::Shape::ShapePtr composite_shape2 = std::make_shared<fomina::CompositeShape>(composite_shape3);
  fomina::Shape::ShapePtr rectangle2 = std::make_shared<fomina::Rectangle>(fomina::Rectangle(WIDTH_R, HEIGHT_R, CENTER_R1));
  fomina::CompositeShape composite_shape1;
  composite_shape1.addShape(composite_shape2);
  composite_shape1.addShape(rectangle2);
  fomina::point_t NEWCENTER_CS = composite_shape1[0]->getCenter();
  fomina::point_t NEWCENTER_R1 = composite_shape1[1]->getCenter();
  const fomina::point_t NEWCENTER1_ = composite_shape1.getCenter();
  fomina::details::rotatePoint(NEWCENTER_CS, NEWCENTER1_, ANGLE);
  fomina::details::rotatePoint(NEWCENTER_R1, NEWCENTER1_, ANGLE);
  composite_shape1.rotate(ANGLE);
  BOOST_CHECK_CLOSE(composite_shape1.getArea(), AREA1, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getFrameRect().width, WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getFrameRect().height, HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getFrameRect().pos.x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getFrameRect().pos.y, CENTER.y, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getCenter().x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getCenter().y, CENTER.y, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1[0]->getCenter().x, NEWCENTER_CS.x, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1[0]->getCenter().y, NEWCENTER_CS.y, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1[1]->getCenter().x, NEWCENTER_R1.x, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1[1]->getCenter().y, NEWCENTER_R1.y, EPSILON);
  BOOST_CHECK(composite_shape.getSize() == 2);
}

BOOST_AUTO_TEST_CASE(CompositeShapeAfterMovingOnAxes)
{
  fomina::CompositeShape composite_shape;
  fomina::Shape::ShapePtr rectangle = std::make_shared<fomina::Rectangle>(fomina::Rectangle(WIDTH_R, HEIGHT_R, CENTER_R));
  fomina::Shape::ShapePtr circle = std::make_shared<fomina::Circle>(fomina::Circle(CENTER_C, RADIUS_C));
  composite_shape.addShape(rectangle);
  composite_shape.addShape(circle);
  composite_shape.move(DX, DY);
  BOOST_CHECK_CLOSE(composite_shape.getArea(), AREA, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().width, WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().height, HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.x, CENTER.x + DX, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.y, CENTER.y + DY, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getCenter().x, CENTER.x + DX, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getCenter().y, CENTER.y + DY, EPSILON);
  BOOST_CHECK(composite_shape.getSize() == 2);

  fomina::CompositeShape composite_shape3;
  fomina::Shape::ShapePtr rectangle1 = std::make_shared<fomina::Rectangle>(fomina::Rectangle(WIDTH_R, HEIGHT_R, CENTER_R));
  fomina::Shape::ShapePtr circle1 = std::make_shared<fomina::Circle>(fomina::Circle(CENTER_C, RADIUS_C));
  composite_shape3.addShape(rectangle1);
  composite_shape3.addShape(circle1);
  fomina::Shape::ShapePtr composite_shape2 = std::make_shared<fomina::CompositeShape>(composite_shape3);
  fomina::Shape::ShapePtr rectangle2 = std::make_shared<fomina::Rectangle>(fomina::Rectangle(WIDTH_R, HEIGHT_R, CENTER_R1));
  fomina::CompositeShape composite_shape1;
  composite_shape1.addShape(composite_shape2);
  composite_shape1.addShape(rectangle2);
  composite_shape1.move(DX, DY);
  BOOST_CHECK_CLOSE(composite_shape1.getArea(), AREA1, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getFrameRect().width, WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getFrameRect().height, HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getFrameRect().pos.x, CENTER.x + DX, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getFrameRect().pos.y, CENTER.y + DY, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getCenter().x, CENTER.x + DX, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getCenter().y, CENTER.y + DY, EPSILON);
  BOOST_CHECK(composite_shape1.getSize() == 2);
}

BOOST_AUTO_TEST_CASE(CompositeShapeAfterMovingInPoint)
{
  fomina::CompositeShape composite_shape;
  fomina::Shape::ShapePtr rectangle = std::make_shared<fomina::Rectangle>(fomina::Rectangle(WIDTH_R, HEIGHT_R, CENTER_R));
  fomina::Shape::ShapePtr circle = std::make_shared<fomina::Circle>(fomina::Circle(CENTER_C, RADIUS_C));
  composite_shape.addShape(rectangle);
  composite_shape.addShape(circle);
  composite_shape.move(MOVEPOINT);
  BOOST_CHECK_CLOSE(composite_shape.getArea(), AREA, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().width, WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().height, HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.x, MOVEPOINT.x, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.y, MOVEPOINT.y, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getCenter().x, MOVEPOINT.x, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape.getCenter().y, MOVEPOINT.y, EPSILON);
  BOOST_CHECK(composite_shape.getSize() == 2);

  fomina::CompositeShape composite_shape3;
  fomina::Shape::ShapePtr rectangle1 = std::make_shared<fomina::Rectangle>(fomina::Rectangle(WIDTH_R, HEIGHT_R, CENTER_R));
  fomina::Shape::ShapePtr circle1 = std::make_shared<fomina::Circle>(fomina::Circle(CENTER_C, RADIUS_C));
  composite_shape3.addShape(rectangle1);
  composite_shape3.addShape(circle1);
  fomina::Shape::ShapePtr composite_shape2 = std::make_shared<fomina::CompositeShape>(composite_shape3);
  fomina::Shape::ShapePtr rectangle2 = std::make_shared<fomina::Rectangle>(fomina::Rectangle(WIDTH_R, HEIGHT_R, CENTER_R1));
  fomina::CompositeShape composite_shape1;
  composite_shape1.addShape(composite_shape2);
  composite_shape1.addShape(rectangle2);
  composite_shape1.move(MOVEPOINT);
  BOOST_CHECK_CLOSE(composite_shape1.getArea(), AREA1, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getFrameRect().width, WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getFrameRect().height, HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getFrameRect().pos.x, MOVEPOINT.x, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getFrameRect().pos.y, MOVEPOINT.y, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getCenter().x, MOVEPOINT.x, EPSILON);
  BOOST_CHECK_CLOSE(composite_shape1.getCenter().y, MOVEPOINT.y, EPSILON);
  BOOST_CHECK(composite_shape1.getSize() == 2);
}

BOOST_AUTO_TEST_CASE(CompositeShapeCopyConstructor)
{
  fomina::CompositeShape composite_shape;
  fomina::Shape::ShapePtr rectangle = std::make_shared<fomina::Rectangle>(fomina::Rectangle(WIDTH_R, HEIGHT_R, CENTER_R));
  fomina::Shape::ShapePtr circle = std::make_shared<fomina::Circle>(fomina::Circle(CENTER_C, RADIUS_C));
  composite_shape.addShape(rectangle);
  composite_shape.addShape(circle);
  fomina::CompositeShape composite_shape4(composite_shape);
  BOOST_CHECK(composite_shape4[0] == composite_shape[0]);
  BOOST_CHECK(composite_shape4[1] == composite_shape[1]);
  BOOST_CHECK(composite_shape4.getArea() == composite_shape.getArea());
  BOOST_CHECK(composite_shape4.getFrameRect().width == composite_shape.getFrameRect().width);
  BOOST_CHECK(composite_shape4.getFrameRect().height == composite_shape.getFrameRect().height);
  BOOST_CHECK(composite_shape4.getFrameRect().pos.x == composite_shape.getFrameRect().pos.x);
  BOOST_CHECK(composite_shape4.getFrameRect().pos.y == composite_shape.getFrameRect().pos.y);
  BOOST_CHECK(composite_shape4.getCenter().x == composite_shape.getCenter().x);
  BOOST_CHECK(composite_shape4.getCenter().y == composite_shape.getCenter().y);
  BOOST_CHECK(composite_shape4.getSize() == composite_shape.getSize());

  fomina::CompositeShape composite_shape3;
  fomina::Shape::ShapePtr rectangle1 = std::make_shared<fomina::Rectangle>(fomina::Rectangle(WIDTH_R, HEIGHT_R, CENTER_R));
  fomina::Shape::ShapePtr circle1 = std::make_shared<fomina::Circle>(fomina::Circle(CENTER_C, RADIUS_C));
  composite_shape3.addShape(rectangle1);
  composite_shape3.addShape(circle1);
  fomina::Shape::ShapePtr composite_shape2 = std::make_shared<fomina::CompositeShape>(composite_shape3);
  fomina::Shape::ShapePtr rectangle2 = std::make_shared<fomina::Rectangle>(fomina::Rectangle(WIDTH_R, HEIGHT_R, CENTER_R1));
  fomina::CompositeShape composite_shape1;
  composite_shape1.addShape(composite_shape2);
  composite_shape1.addShape(rectangle2);
  fomina::CompositeShape composite_shape5(composite_shape1);
  BOOST_CHECK(composite_shape5[0] == composite_shape1[0]);
  BOOST_CHECK(composite_shape5[1] == composite_shape1[1]);
  BOOST_CHECK(composite_shape5.getArea() == composite_shape1.getArea());
  BOOST_CHECK(composite_shape5.getFrameRect().width == composite_shape1.getFrameRect().width);
  BOOST_CHECK(composite_shape5.getFrameRect().height == composite_shape1.getFrameRect().height);
  BOOST_CHECK(composite_shape5.getFrameRect().pos.x == composite_shape1.getFrameRect().pos.x);
  BOOST_CHECK(composite_shape5.getFrameRect().pos.y == composite_shape1.getFrameRect().pos.y);
  BOOST_CHECK(composite_shape5.getCenter().x == composite_shape1.getCenter().x);
  BOOST_CHECK(composite_shape5.getCenter().y == composite_shape1.getCenter().y);
  BOOST_CHECK(composite_shape5.getSize() == composite_shape1.getSize());
}

BOOST_AUTO_TEST_CASE(CompositeShapeCopyOperator)
{
  fomina::CompositeShape composite_shape;
  fomina::Shape::ShapePtr rectangle = std::make_shared<fomina::Rectangle>(fomina::Rectangle(WIDTH_R, HEIGHT_R, CENTER_R));
  fomina::Shape::ShapePtr circle = std::make_shared<fomina::Circle>(fomina::Circle(CENTER_C, RADIUS_C));
  composite_shape.addShape(rectangle);
  composite_shape.addShape(circle);
  fomina::CompositeShape composite_shape4 = composite_shape;
  BOOST_CHECK(composite_shape4[0] == composite_shape[0]);
  BOOST_CHECK(composite_shape4[1] == composite_shape[1]);
  BOOST_CHECK(composite_shape4.getArea() == composite_shape.getArea());
  BOOST_CHECK(composite_shape4.getFrameRect().width == composite_shape.getFrameRect().width);
  BOOST_CHECK(composite_shape4.getFrameRect().height == composite_shape.getFrameRect().height);
  BOOST_CHECK(composite_shape4.getFrameRect().pos.x == composite_shape.getFrameRect().pos.x);
  BOOST_CHECK(composite_shape4.getFrameRect().pos.y == composite_shape.getFrameRect().pos.y);
  BOOST_CHECK(composite_shape4.getCenter().x == composite_shape.getCenter().x);
  BOOST_CHECK(composite_shape4.getCenter().y == composite_shape.getCenter().y);
  BOOST_CHECK(composite_shape4.getSize() == composite_shape.getSize());

  fomina::CompositeShape composite_shape3;
  fomina::Shape::ShapePtr rectangle1 = std::make_shared<fomina::Rectangle>(fomina::Rectangle(WIDTH_R, HEIGHT_R, CENTER_R));
  fomina::Shape::ShapePtr circle1 = std::make_shared<fomina::Circle>(fomina::Circle(CENTER_C, RADIUS_C));
  composite_shape3.addShape(rectangle1);
  composite_shape3.addShape(circle1);
  fomina::Shape::ShapePtr composite_shape2 = std::make_shared<fomina::CompositeShape>(composite_shape3);
  fomina::Shape::ShapePtr rectangle2 = std::make_shared<fomina::Rectangle>(fomina::Rectangle(WIDTH_R, HEIGHT_R, CENTER_R1));
  fomina::CompositeShape composite_shape1;
  composite_shape1.addShape(composite_shape2);
  composite_shape1.addShape(rectangle2);
  fomina::CompositeShape composite_shape5 = composite_shape1;
  BOOST_CHECK(composite_shape5[0] == composite_shape1[0]);
  BOOST_CHECK(composite_shape5[1] == composite_shape1[1]);
  BOOST_CHECK(composite_shape5.getArea() == composite_shape1.getArea());
  BOOST_CHECK(composite_shape5.getFrameRect().width == composite_shape1.getFrameRect().width);
  BOOST_CHECK(composite_shape5.getFrameRect().height == composite_shape1.getFrameRect().height);
  BOOST_CHECK(composite_shape5.getFrameRect().pos.x == composite_shape1.getFrameRect().pos.x);
  BOOST_CHECK(composite_shape5.getFrameRect().pos.y == composite_shape1.getFrameRect().pos.y);
  BOOST_CHECK(composite_shape5.getCenter().x == composite_shape1.getCenter().x);
  BOOST_CHECK(composite_shape5.getCenter().y == composite_shape1.getCenter().y);
  BOOST_CHECK(composite_shape5.getSize() == composite_shape1.getSize());
}

BOOST_AUTO_TEST_CASE(CompositeShapeInvalidShape)
{
  fomina::CompositeShape composite_shape;
  BOOST_CHECK_THROW(composite_shape.addShape(nullptr), std::invalid_argument);
  std::shared_ptr<fomina::CompositeShape> composite_shape1 = std::make_shared<fomina::CompositeShape>(composite_shape);
  BOOST_CHECK_THROW(composite_shape1->addShape(composite_shape1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(CompositeShapeInvalidIndex)
{
  fomina::CompositeShape composite_shape;
  fomina::Shape::ShapePtr rectangle = std::make_shared<fomina::Rectangle>(fomina::Rectangle(WIDTH_R, HEIGHT_R, CENTER_R));
  composite_shape.addShape(rectangle);
  BOOST_CHECK_THROW(composite_shape.deleteShape(1), std::invalid_argument);
  BOOST_CHECK_THROW(composite_shape.deleteShape(-1), std::invalid_argument);
  BOOST_CHECK_THROW(composite_shape[1], std::invalid_argument);
  BOOST_CHECK_THROW(composite_shape[-1], std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(CompositeShapeInvalidCoef)
{
  fomina::CompositeShape composite_shape;
  BOOST_CHECK_THROW(composite_shape.scale(-COEF), std::invalid_argument);
  BOOST_CHECK_THROW(composite_shape.scale(0), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
