#include <stdexcept>
#include <random>
#include <vector>

#include "utility.hpp"

void fillRandom(double* array, int size)
{
  if (size <= 0)
  {
    throw std::invalid_argument("Size must be > 0");
  }

  std::random_device random_device;
  std::mt19937 generator(random_device());
  std::uniform_real_distribution<> distribution(-1.0, 1.0);
  for (int i = 0; i < size; i++)
  {
    array[i] = distribution(generator);
  }
}

void task4(std::function<bool(double, double)> comparator, const size_t size)
{
  if (size == 0)
  {
    throw std::invalid_argument("Size must be > 0");
  }

  std::vector<double> vector (size);
  fillRandom(vector.data(), size);
  print(vector);

  sort<std::vector<double>, AccessByIndex>(vector, comparator);
  print(vector);
}
