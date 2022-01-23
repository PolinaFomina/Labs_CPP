#include <iostream>

#include "factorial-container.hpp"

void task2(std::ostream& out)
{
  FactorialContainer container(11);

  std::copy(container.begin(), container.end(), std::ostream_iterator<size_t>(out, " "));
  out << '\n';
  std::copy(container.rbegin(), container.rend(), std::ostream_iterator<size_t>(out, " "));
  out << '\n';
}
