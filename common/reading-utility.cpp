#include "reading-utility.hpp"

#include <iostream>

StreamGuard::StreamGuard(std::istream& in):
  stream(in)
{
  flags = stream.flags();
}

StreamGuard::~StreamGuard()
{
  stream.setf(flags);
}

std::istream& skipSpaces(std::istream& in)
{
  while (in && isspace(in.peek()))
  {
    if (in.peek() == '\n')
    {
      break;
    }
    else
    {
      in.get();
    }
  }

  return in;
}
