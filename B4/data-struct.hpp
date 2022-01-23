#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <string>
#include <iostream>

struct DataStruct
{
  int key1;
  int key2;
  std::string str;
};

std::istream& operator>>(std::istream& in, DataStruct& dataStruct);
std::ostream& operator<<(std::ostream& out, const DataStruct& dataStruct);
bool operator<(const DataStruct& dataStruct1, const DataStruct& dataStruct2);

#endif
