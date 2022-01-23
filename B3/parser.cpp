#include "parser.hpp"

#include <string>
#include <sstream>
#include <unordered_map>
#include <functional>
#include <cctype>
#include <iterator>
#include <cstdlib>

#include "commands.hpp"
#include "reading-utility.hpp"

CommandType parse(std::istringstream& stream)
{
  std::string command;
  stream >> command;
  if (stream.fail())
  {
    throw std::runtime_error("Read error");
  }

  const std::unordered_map<std::string, CommandType(*)(std::istringstream&)> commandMap
  {
    {"add", &parseAdd},
    {"store", &parseStore},
    {"insert", &parseInsert},
    {"delete", &parseDelete},
    {"show", &parseShow},
    {"move", &parseMove}
  };

  auto iterator = commandMap.find(command);
  if (iterator == commandMap.end())
  {
    return std::bind(&printInvalidCommand, std::placeholders::_3);
  }
  else
  {
    return iterator->second(stream);
  }
}

CommandType parseAdd(std::istringstream& stream)
{
  std::string number, name;
  stream >> number;
  if (stream.fail())
  {
    throw std::runtime_error("Read error");
  }
  if (!isCorrectNumber(number))
  {
    return std::bind(&printInvalidCommand, std::placeholders::_3);
  }

  stream >> std::ws;
  readName(stream, name);
  if (stream.fail())
  {
    return std::bind(&printInvalidCommand, std::placeholders::_3);
  }

  std::string otherString;
  if (!(stream >> std::ws).eof())
  {
    std::getline(stream, otherString);
    return std::bind(&printInvalidCommand, std::placeholders::_3);
  }

  return std::bind(&add, std::placeholders::_1, std::placeholders::_2, name, number);
}

CommandType parseStore(std::istringstream& stream)
{
  std::string markName, newMarkName;
  stream >> markName;
  if (stream.fail())
  {
    throw std::runtime_error("Read error");
  }
  if (!isCorrectMarkName(markName))
  {
    return std::bind(&printInvalidCommand, std::placeholders::_3);
  }

  stream >> newMarkName;
  if (stream.fail())
  {
    throw std::runtime_error("Read error");
  }
  if (!isCorrectMarkName(newMarkName))
  {
    return std::bind(&printInvalidCommand, std::placeholders::_3);
  }

  std::string otherString;
  if (!(stream >> std::ws).eof())
  {
    std::getline(stream, otherString);
    return std::bind(&printInvalidCommand, std::placeholders::_3);
  }

  return std::bind(&store, std::placeholders::_2, std::placeholders::_3, markName, newMarkName);
}

CommandType parseInsert(std::istringstream& stream)
{
  std::string position, markName, number, name;
  stream >> position;
  if (stream.fail())
  {
    throw std::runtime_error("Read error");
  }

  stream >> markName;
  if (stream.fail())
  {
    throw std::runtime_error("Read error");
  }
  if (!isCorrectMarkName(markName))
  {
    return std::bind(&printInvalidCommand, std::placeholders::_3);
  }

  stream >> number;
  if (stream.fail())
  {
    throw std::runtime_error("Read error");
  }
  if (!isCorrectNumber(number))
  {
    return std::bind(&printInvalidCommand, std::placeholders::_3);
  }

  stream >> std::ws;
  readName(stream, name);
  if (stream.fail())
  {
    return std::bind(&printInvalidCommand, std::placeholders::_3);
  }

  std::string otherString;
  if (!(stream >> std::ws).eof())
  {
    std::getline(stream, otherString);
    return std::bind(&printInvalidCommand, std::placeholders::_3);
  }

  if (position == "before")
  {
    return std::bind(&insertBefore, std::placeholders::_1, std::placeholders::_2,
        std::placeholders::_3, markName, name, number);
  }
  else if (position == "after")
  {
    return std::bind(&insertAfter, std::placeholders::_1, std::placeholders::_2,
        std::placeholders::_3, markName, name, number);
  }
  else
  {
    return std::bind(&printInvalidCommand, std::placeholders::_3);
  }
}

CommandType parseDelete(std::istringstream& stream)
{
  std::string markName;
  stream >> markName;
  if (stream.fail())
  {
    throw std::runtime_error("Read error");
  }
  if (!isCorrectMarkName(markName))
  {
    return std::bind(&printInvalidCommand, std::placeholders::_3);
  }

  std::string otherString;
  if (!(stream >> std::ws).eof())
  {
    std::getline(stream, otherString);
    return std::bind(&printInvalidCommand, std::placeholders::_3);
  }

  return std::bind(&deleteRecord, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, markName);
}

CommandType parseShow(std::istringstream& stream)
{
  std::string markName;
  stream >> markName;
  if (stream.fail())
  {
    throw std::runtime_error("Read error");
  }
  if (!isCorrectMarkName(markName))
  {
    return std::bind(&printInvalidCommand, std::placeholders::_3);
  }

  std::string otherString;
  if (!(stream >> std::ws).eof())
  {
    std::getline(stream, otherString);
    return std::bind(&printInvalidCommand, std::placeholders::_3);
  }

  return std::bind(&show, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, markName);
}

CommandType parseMove(std::istringstream& stream)
{
  std::string markName, position;
  stream >> markName;
  if (stream.fail())
  {
    throw std::runtime_error("Read error");
  }
  if (!isCorrectMarkName(markName))
  {
    return std::bind(&printInvalidCommand, std::placeholders::_3);
  }

  stream >> position;
  if (stream.fail())
  {
    throw std::runtime_error("Read error");
  }
  if (position.empty())
  {
    return std::bind(&printInvalidStep, std::placeholders::_3);
  }

  std::string otherString;
  if (!(stream >> std::ws).eof())
  {
    std::getline(stream, otherString);
    return std::bind(&printInvalidCommand, std::placeholders::_3);
  }

  char* end = nullptr;
  long int step = std::strtol(position.c_str(), &end, 10);
  if (errno == ERANGE)
  {
    return std::bind(&printInvalidStep, std::placeholders::_3);
  }
  else if (*end != '\0')
  {
    return std::bind(&moveInPosition, std::placeholders::_1, std::placeholders::_2,
        std::placeholders::_3, markName, position);
  }

  return std::bind(&moveOnStep, std::placeholders::_1, std::placeholders::_2,
      std::placeholders::_3, markName, step);
}
