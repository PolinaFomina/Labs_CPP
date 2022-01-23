#include <iostream>
#include <vector>
#include <iterator>
#include <stdexcept>
#include <algorithm>

#include "Statistics.hpp"

void task(std::istream& in, std::ostream& out)
{
  auto statistics = std::for_each(std::istream_iterator<long long int>(in),
      std::istream_iterator<long long int>(), Statistics());

  if (!in.eof())
  {
    throw std::runtime_error("Reading failed");
  }

  out << statistics;
}
