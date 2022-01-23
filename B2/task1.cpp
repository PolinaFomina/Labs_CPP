#include <iostream>
#include <string>
#include <functional>

#include "queue.hpp"
#include "parser.hpp"

void task1(std::istream& in, std::ostream& out)
{
  QueueWithPriority<std::string> queue;
  std::string string;
  while (std::getline(in, string))
  {
    CommandType command = parse(string);
    command(out, queue);
  }
}
