#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <iostream>
#include <functional>
#include <stdexcept>
#include <cstring>
#include <algorithm>

#include "access.hpp"

template<typename TypeValue>
std::function<bool(const TypeValue, const TypeValue)> defineOrder(const char* order)
{
  if (order == nullptr)
  {
    throw std::invalid_argument("Parametr is absent");
  }
  if (!strcmp(order, "ascending"))
  {
    return std::less<const TypeValue>();
  }
  if (!strcmp(order, "descending"))
  {
    return std::greater<const TypeValue>();
  }
  throw std::invalid_argument("Incorrect parametr");
}

template <typename TypeCollection, template <typename> class TypeAccess>
void sort(TypeCollection& collection, std::function<bool(const typename TypeCollection::value_type, 
    const typename TypeCollection::value_type)> comparator)
{
  using access = TypeAccess<TypeCollection>;

  for (auto i = access::begin(collection); i != access::end(collection); i++)
  {
    for (auto j = i; j != access::end(collection); j++)
    {
      if (comparator(access::get(collection, j), access::get(collection, i)))
      {
        std::swap(access::get(collection, j), access::get(collection, i));
      }
    }
  }
};

template <typename TypeCollection>
void print(const TypeCollection& collection)
{
  for (auto i = collection.begin(); i != collection.end(); i++)
  {
    std::cout << *i << " ";
  }
  std::cout << "\n";
};

#endif
