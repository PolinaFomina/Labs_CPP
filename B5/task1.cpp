#include <iostream>
#include <unordered_set>
#include <string>
#include <iterator>
#include <stdexcept>
#include <algorithm>

void task1(std::istream& in, std::ostream& out)
{
  std::unordered_set<std::string> set((std::istream_iterator<std::string>(in)), std::istream_iterator<std::string>());

  if (!in.eof())
  {
    throw std::runtime_error("Reading failed");
  }

  std::copy(set.begin(), set.end(), std::ostream_iterator<std::string>(out, "\n"));
}
