#include <iostream>
#include <stdexcept>

void task(std::istream& in, std::ostream& out);

int main()
{
  try
  {
    try
    {
      task(std::cin, std::cout);
    }
    catch (const std::runtime_error& error)
    {
      std::cerr << "Error: " << error.what();
      return 1;
    }
    catch (const std::logic_error& error)
    {
      std::cerr << "Error: " << error.what();
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
