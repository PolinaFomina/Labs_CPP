#include <stdexcept>
#include <iostream>
#include <sstream>

void task1(std::istream& in, std::ostream& out);
void task2(std::ostream& out);

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Input arguments must be 2";
      return 1;
    }
    std::istringstream stream(argv[1]);
    size_t task = 0;
    stream >> task;
    if (stream.fail())
    {
      std::cerr << "Incorrect parametr";
      return 1;
    }
    switch (task)
    {
      case 1:
        try
        {
          task1(std::cin, std::cout);
        }
        catch (const std::runtime_error& error)
        {
          std::cerr << "Error: " << error.what();
          return 2;
        }
        catch (const std::invalid_argument& error)
        {
          std::cerr << "Error: " << error.what();
          return 1;
        }
        break;

      case 2:
        try
        {
          task2(std::cout);
        }
        catch (const std::out_of_range& error)
        {
          std::cerr << "Error: " << error.what();
          return 1;
        }
        catch (const std::overflow_error& error)
        {
          std::cerr << "Error: " << error.what();
          return 1;
        }
        break;

      default:
        std::cerr << "Incorrect number of task";
        return 1;
    }
  }
  catch (const std::exception& error)
  {
    std::cerr << "An unexpected error occurred: " << error.what();
    return 2;
  }
  return 0;
}
