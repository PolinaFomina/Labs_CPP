#include <iostream>
#include <string>
#include <sstream>
#include <iterator>

#include "phone-book.hpp"
#include "marks.hpp"
#include "parser.hpp"

void task1(std::istream& in, std::ostream& out)
{
  PhoneBook PhoneBook;
  Marks Marks(PhoneBook);
  std::string string;
  while (std::getline(in, string))
  {
    std::istringstream stream(string);
    if ((stream >> std::ws).eof())
    {
      continue;
    }
    CommandType command = parse(stream);
    command(PhoneBook, Marks, out);
  }
}
