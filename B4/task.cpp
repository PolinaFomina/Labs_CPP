#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

#include "data-struct.hpp"

void task(std::istream& in, std::ostream& out)
{
  std::vector<DataStruct> vector((std::istream_iterator<DataStruct>(in)), std::istream_iterator<DataStruct>());

  if (!in.eof())
  {
    throw std::runtime_error("Read error");
  }

  std::sort(vector.begin(), vector.end());
  std::copy(vector.begin(), vector.end(), std::ostream_iterator<DataStruct>(out));
}
