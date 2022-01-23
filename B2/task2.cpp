#include <list>
#include <stdexcept>
#include <iostream>

void printList(std::ostream& out, const std::list<int>& list)
{
  if (list.empty())
  {
    return;
  }
  else
  {
    auto begin = list.begin();
    auto end = list.end();
    end--;
    while (begin != end)
    {
      out << *(begin++);
      if (begin == end)
      {
        out << " " << *begin << "\n";
        return;
      }
      out << " " << *(end--) << " ";
    }
    out << *begin << "\n";
  }
}

void task2(std::istream& in, std::ostream& out)
{
  std::list<int> list;
  const size_t maxSize = 20;
  const int minNumber = 1;
  const int maxNumber = 20;
  size_t size = 0;
  int number = 0;

  while (in >> number)
  {
    if (size >= maxSize)
    {
      throw std::runtime_error("The number of numbers mustn't be > 20");
    }
    if (number < minNumber || number > maxNumber)
    {
      throw std::runtime_error("The number must be > 1 and < 20");
    }

    list.push_back(number);
    size++;
  }
  if (!in.eof())
  {
    throw std::runtime_error("Read error");
  }
  if (list.empty())
  {
    return;
  }

  printList(out, list);
}
