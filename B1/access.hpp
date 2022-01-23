#ifndef ACCESS_HPP
#define ACCESS_HPP

#include <stdexcept>
#include <iterator>

template <typename TypeCollection>
class AccessByIndex
{
public:
  using value = typename TypeCollection::value_type;
  using iterator = typename TypeCollection::size_type;
  static iterator begin(const TypeCollection&)
  {
    return 0;
  }
  static iterator end(const TypeCollection& collection)
  {
    return collection.size();
  }
  static value& get(TypeCollection& collection, size_t index)
  {
    if (index >= collection.size())
    {
      throw std::invalid_argument("Index must be in the range [0, size)");
    }
    return collection[index];
  }
};

template <typename TypeCollection>
class AccessByAt
{
public:
  using value = typename TypeCollection::value_type;
  using iterator = typename TypeCollection::size_type;
  static iterator begin(const TypeCollection&)
  {
    return 0;
  }
  static iterator end(const TypeCollection& collection)
  {
    return collection.size();
  }
  static value& get(TypeCollection& collection, size_t index)
  {
    if (index >= collection.size())
    {
      throw std::invalid_argument("Index must be in the range [0, size)");
    }
    return collection.at(index);
  }
};

template <typename TypeCollection>
class AccessByIterator
{
public:
  using value = typename TypeCollection::value_type;
  using iterator = typename TypeCollection::iterator;
  static iterator begin(TypeCollection& collection)
  {
    return collection.begin();
  }
  static iterator end(TypeCollection& collection)
  {
    return collection.end();
  }
  static value& get(TypeCollection&, iterator iterator)
  {
    return *iterator;
  }
};

#endif
