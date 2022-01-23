#ifndef PARSER_HPP
#define PARSER_HPP

#include <functional>
#include <sstream>
#include <string>

#include "queue.hpp"

using Priority = QueueWithPriority<std::string>::ElementPriority;
using CommandType = std::function<void(std::ostream&, QueueWithPriority<std::string>&)>;

CommandType parse(std::string& string);
CommandType parseAdd(std::istringstream& stream);
CommandType parseGet(std::istringstream& stream);
CommandType parseAccelerate(std::istringstream& stream);

#endif
