#include <fstream>
#include <memory>
#include <stdexcept>
#include <vector>

#include "utility.hpp"

void task2(const char* fileName)
{
  if (fileName == nullptr)
  {
    throw std::invalid_argument("File name is absent");
  }
  std::ifstream file(fileName);
  if (!file)
  {
    throw std::invalid_argument("File isn't open");
  }
  if (file.eof())
  {
    return;
  }

  size_t arraySize = 1;
  std::unique_ptr<char[], decltype(&free)> array(static_cast<char*>(malloc(arraySize)), &free);
  if (!array)
  {
    throw std::bad_alloc();
  }

  size_t elementsCount = 0;
  while (file)
  {
    file.read(&array[elementsCount], arraySize - elementsCount);
    elementsCount += file.gcount();
    if (elementsCount == arraySize)
    {
      arraySize *= 2;
      std::unique_ptr<char[], decltype(&free)> temp(static_cast<char*>(realloc(array.get(), arraySize)), &free);
      if (!temp)
      {
        throw std::bad_alloc();
      }

      std::swap(array, temp);
      temp.release();
    }
  }

  std::vector<char> vector(array.get(), array.get() + elementsCount);
  for (auto i = vector.begin(); i != vector.end(); i++)
  {
    std::cout << *i;
  }
}
