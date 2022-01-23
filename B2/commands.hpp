#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <string>

#include "queue.hpp"

using Queue = QueueWithPriority<std::string>;
using Priority = QueueWithPriority<std::string>::ElementPriority;

void add(Queue& queue, const Priority priority, const std::string& data);
void get(std::ostream& out, Queue& queue);
void accelerate(Queue& queue);
void printInvalidCommand(std::ostream& out);

#endif
