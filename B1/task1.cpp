#include <vector>
#include <stdexcept>
#include <iostream>
#include <forward_list>
#include "utility.hpp"

void task1(std::function<bool(int, int)> comparator)
{
  std::vector<int> vector1;
  int number = 0;

  while (std::cin >> number)
  {
    vector1.push_back(number);
  }
  if (!std::cin.eof())
  {
    throw std::invalid_argument("Incorrect input");
  }
  if (vector1.empty())
  {
    return;
  }

  std::vector<int> vector2(vector1);
  std::forward_list<int> list(vector1.begin(), vector1.end());

  sort<std::vector<int>, AccessByIndex>(vector1, comparator);
  print(vector1);

  sort<std::vector<int>, AccessByAt>(vector2, comparator);
  print(vector2);

  sort<std::forward_list<int>, AccessByIterator>(list, comparator);
  print(list);
}
