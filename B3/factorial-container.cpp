#include "factorial-container.hpp"

#include <climits>
#include <stdexcept>
#include <iterator>
#include <cassert>

static size_t getFactorial(const size_t value)
{
  if (value > 1)
  {
    size_t factorial = 1;
    for (size_t i = 2; i <= value; i++)
    {
      if (factorial > (UINT_MAX / i))
      {
        throw std::overflow_error("Factorial value over then max of size_t");
      }
      factorial *= i;
    }
    return factorial;
  }
  return 1;
}

FactorialContainer::Iterator::Iterator(size_t maxPosition, size_t minPosition, size_t position, value_type value):
  maxPosition(maxPosition),
  minPosition(minPosition),
  position(position),
  value(value)
{
  assert((position <= maxPosition) && (position >= minPosition));
}

FactorialContainer::Iterator::value_type FactorialContainer::Iterator::operator*() const
{
  return value;
}

FactorialContainer::Iterator& FactorialContainer::Iterator::operator++()
{
  if (position == maxPosition)
  {
    throw std::out_of_range("The iterator went outside the container");
  }

  position++;
  value *= position;
  return *this;
}

FactorialContainer::Iterator& FactorialContainer::Iterator::operator--()
{
  if (position == minPosition)
  {
    throw std::out_of_range("The iterator went outside the container");
  }

  value /= position;
  position--;
  return *this;
}

FactorialContainer::Iterator FactorialContainer::Iterator::operator++(int)
{
  Iterator temp = *this;
  ++(*this);
  return temp;
}

FactorialContainer::Iterator FactorialContainer::Iterator::operator--(int)
{
  Iterator temp = *this;
  --(*this);
  return temp;
}

bool FactorialContainer::Iterator::operator==(const Iterator& iterator) const
{
  return ((maxPosition == iterator.maxPosition) && (minPosition == iterator.minPosition)
      && (position == iterator.position) && (value == iterator.value));
}

bool FactorialContainer::Iterator::operator!=(const Iterator& iterator) const
{
  return ((maxPosition != iterator.maxPosition) || (minPosition != iterator.minPosition)
      || (position != iterator.position) || (value != iterator.value));
}

FactorialContainer::FactorialContainer(size_t size):
  size(size),
  maxValue(getFactorial(size))
{
}

FactorialContainer::const_iterator FactorialContainer::begin() const
{
  return Iterator(size, 1, 1, 1);
}

FactorialContainer::const_iterator FactorialContainer::end() const
{
  return Iterator(size, 1, size, maxValue);
}

FactorialContainer::const_reverse_iterator FactorialContainer::rbegin() const
{
  return const_reverse_iterator(end());
}

FactorialContainer::const_reverse_iterator FactorialContainer::rend() const
{
  return const_reverse_iterator(begin());
}
