#include <functional>
#include <string>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

#include "parser.hpp"
#include "commands.hpp"

CommandType parse(std::string& string)
{
  std::istringstream stream(string);
  std::string command;
  stream >> command;
  if (stream.fail())
  {
    throw std::runtime_error("Read error");
  }

  const std::unordered_map<std::string, CommandType(*)(std::istringstream&)> commandMap
  {
    {"add", &parseAdd},
    {"get", &parseGet},
    {"accelerate", &parseAccelerate}
  };

  auto iterator = commandMap.find(command);
  if (iterator == commandMap.end())
  {
    return std::bind(&printInvalidCommand, std::placeholders::_1);
  }
  else
  {
    return iterator->second(stream);
  }
}

CommandType parseAdd(std::istringstream& stream)
{
  std::string stringPriority, data;
  Priority priority;
  stream >> stringPriority >> std::ws;
  if (stream.fail())
  {
    throw std::runtime_error("Read error");
  }
  std::getline(stream, data);

  if (data.empty())
  {
    return std::bind(&printInvalidCommand, std::placeholders::_1);
  }

  const std::unordered_map<std::string, Priority> priorityMap
  {
    {"high", Priority::HIGH},
    {"normal", Priority::NORMAL},
    {"low", Priority::LOW}
  };

  auto iterator = priorityMap.find(stringPriority);
  if (iterator == priorityMap.end())
  {
    return std::bind(&printInvalidCommand, std::placeholders::_1);
  }
  else
  {
    priority = iterator->second;
  }

  return std::bind(&add, std::placeholders::_2, priority, data);
}

CommandType parseGet(std::istringstream& stream)
{
  std::string otherString;
  if (!(stream >> std::ws).eof())
  {
    std::getline(stream, otherString);
    return std::bind(&printInvalidCommand, std::placeholders::_1);
  }

  return &get;
}

CommandType parseAccelerate(std::istringstream& stream)
{
  std::string otherString;
  if (!(stream >> std::ws).eof())
  {
    std::getline(stream, otherString);
    return std::bind(&printInvalidCommand, std::placeholders::_1);
  }

  return std::bind(&accelerate, std::placeholders::_2);
}
