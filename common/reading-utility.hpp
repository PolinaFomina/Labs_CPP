#ifndef READINGUTILITY_HPP
#define READINGUTILITY_HPP

#include <iostream>

class StreamGuard
{
public:
  StreamGuard(std::istream& in);
  ~StreamGuard();
private:
  std::istream& stream;
  std::istream::fmtflags flags;
};

std::istream& skipSpaces(std::istream& in);

#endif
