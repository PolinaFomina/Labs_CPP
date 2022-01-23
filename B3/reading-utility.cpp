#include "reading-utility.hpp"

#include <sstream>
#include <string>

void readName(std::istringstream& stream, std::string& name)
{
  if (stream.get() != '"')
  {
    stream.setstate(std::ios::failbit);
    return;
  }
  name.push_back(stream.get());
  while (stream && !((stream.peek() == '"') && (name.back() != '\\')))
  {
    if ((name.back() == '\\') && ((stream.peek() == '"') || (stream.peek() == '\\')))
    {
      name.pop_back();
    }
    name.push_back(stream.get());
  }
  if (stream.eof())
  {
    stream.setstate(std::ios::failbit);
    return;
  }
  stream.get();
}

bool isCorrectNumber(const std::string& number)
{
  if (number.empty())
  {
    return false;
  }
  for (size_t i = 0; i < number.size(); i++)
  {
    if (!isdigit(number[i]))
    {
      return false;
    }
  }
  return true;
}

bool isCorrectMarkName(const std::string& markName)
{
  if (markName.empty())
  {
    return false;
  }
  for (size_t i = 0; i < markName.size(); i++)
  {
    if ((!isalnum(markName[i])) && (markName[i] != '-'))
    {
      return false;
    }
  }
  return true;
}
