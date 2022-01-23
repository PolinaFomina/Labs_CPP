#include <iostream>

#include "commands.hpp"

void add(Queue& queue, const Priority priority, const std::string& data)
{
  queue.put(data, priority);
}

void get(std::ostream& out, Queue& queue)
{
  if (queue.isEmpty())
  {
    out << "<EMPTY>\n";
  }
  else
  {
    std::string element;
    queue.get(element);
    out << element << "\n";
  }
}

void accelerate(Queue& queue)
{
  queue.accelerate();
}

void printInvalidCommand(std::ostream& out)
{
  out << "<INVALID COMMAND>\n";
}
