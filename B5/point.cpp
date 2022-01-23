#include "point.hpp"

#include <iostream>

#include "reading-utility.hpp"

std::istream& operator>>(std::istream& in, Point& point)
{
  StreamGuard stream(in);

  in >> std::noskipws;

  char bracket1;
  in >> skipSpaces >> bracket1;
  if (in.fail())
  {
    return in;
  }
  if (bracket1 != '(')
  {
    in.unget();
    in.setstate(std::ios::failbit);
    return in;
  }

  int x;
  in >> skipSpaces >> x;
  if (in.fail())
  {
    return in;
  }

  char sep;
  in >> skipSpaces >> sep;
  if (in.fail())
  {
    return in;
  }
  if (sep != ';')
  {
    in.unget();
    in.setstate(std::ios::failbit);
    return in;
  }

  int y;
  in >> skipSpaces >> y;
  if (in.fail())
  {
    return in;
  }

  char bracket2;
  in >> skipSpaces >> bracket2 >> skipSpaces;
  if (in.fail())
  {
    throw std::runtime_error("Read error");
  }

  if (bracket2 != ')')
  {
    in.unget();
    in.setstate(std::ios::failbit);
    return in;
  }

  point = { x, y };

  return in;
}

std::ostream& operator<<(std::ostream& out, const Point& point)
{
  std::ostream::sentry sentry(out);
  if (sentry)
  {
    out << '(' << point.x << ';' << point.y << ')';
  }

  return out;
}
