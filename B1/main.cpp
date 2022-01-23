#include <stdexcept>
#include <iostream>
#include <sstream>

#include "utility.hpp"

void task1(std::function<bool(int, int)> comparator);
void task2(const char* fileName);
void task3();
void task4(std::function<bool(double, double)> comparator, const size_t size);

int main(int argc, char* argv[])
{
  try
  {
    if ((argc < 2) || (argc > 4))
    {
      std::cerr << "Incorrect input arguments";
      return 1;
    }
    std::istringstream string(argv[1]);
    size_t task = 0;
    string >> task;
    if (string.fail())
    {
      std::cerr << "Incorrect parametr";
      return 1;
    }
    switch (task)
    {
      case 1:
      if (argc != 3)
      {
        std::cerr << "Input arguments must be 3";
        return 1;
      }
      try
      {
        auto order = defineOrder<int>(argv[2]);
        task1(order);
      }
      catch (const std::invalid_argument& error)
      {
        std::cerr << "Error: " << error.what();
        return 1;
      }
      break;

      case 2:
      if (argc != 3)
      {
        std::cerr << "Input arguments must be 3";
        return 1;
      }
      try
      {
        task2(argv[2]);
      }
      catch (const std::bad_alloc& error)
      {
        std::cerr << "Allocation error" << "\n";
        return 2;
      }
      catch (const std::invalid_argument& error)
      {
        std::cerr << "Error: " << error.what();
        return 1;
      }
      break;

      case 3:
      if (argc != 2)
      {
        std::cerr << "Input arguments must be 2";
        return 1;
      }
      try
      {
        task3();
      }
      catch (const std::invalid_argument& error)
      {
        std::cerr << "Error: " << error.what();
        return 1;
      }
      break;

      case 4:
      if (argc != 4)
      {
        std::cerr << "Input arguments must be 4";
        return 1;
      }
      try
      {
        std::istringstream stream(argv[3]);
        size_t size = 0;
        stream >> size;
        if (stream.fail())
        {
          std::cerr << "Incorrect parametr";
          return 1;
        }
        auto order = defineOrder<double>(argv[2]);
        task4(order, size);
      }
      catch (const std::invalid_argument& error)
      {
        std::cerr << "Error: " << error.what();
        return 1;
      }
      break;

      default:
      {
        std::cerr << "Incorrect number of task";
        return 1;
      }
    }
  }
  catch (std::exception& error)
  {
    std::cerr << "An unexpected error occurred: " << error.what();
    return 2;
  }
  return 0;
}
