#include "data-struct.hpp"

#include <iostream>
#include <string>
#include <stdexcept>
#include <cmath>

#include "reading-utility.hpp"

const int maxValue = 5;

std::istream& operator>>(std::istream& in, DataStruct& dataStruct)
{
  StreamGuard stream(in);
  int key1, key2;
  char sep1, sep2;
  std::string str;

  in >> std::noskipws;

  in >> skipSpaces >> key1;
  if (in.fail())
  {
    return in;
  }

  in >> skipSpaces >> sep1;
  if (in.fail())
  {
    return in;
  }

  in >> skipSpaces >> key2;
  if (in.fail())
  {
    return in;
  }

  in >> skipSpaces >> sep2 >> skipSpaces;
  if (in.fail())
  {
    return in;
  }

  std::getline(in, str);
  if (in.fail())
  {
    throw std::runtime_error("Read error");
  }

  if ((std::abs(key1) > maxValue) || (std::abs(key2) > maxValue))
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  if (sep1 != ',' || sep2 != ',')
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  dataStruct = { key1, key2, str };

  return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& dataStruct)
{
  out << dataStruct.key1 << "," << dataStruct.key2 << "," << dataStruct.str << '\n';
  return out;
}

bool operator<(const DataStruct& dataStruct1, const DataStruct& dataStruct2)
{
  if (dataStruct1.key1 == dataStruct2.key1)
  {
    if (dataStruct1.key2 == dataStruct2.key2)
    {
      return dataStruct1.str.size() < dataStruct2.str.size();
    }

    return dataStruct1.key2 < dataStruct2.key2;
  }

  return dataStruct1.key1 < dataStruct2.key1;
}
