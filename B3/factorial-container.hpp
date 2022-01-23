#ifndef FACTORIALCONTAINER_HPP
#define FACTORIALCONTAINER_HPP

#include <iterator>

class FactorialContainer
{
public:

  class Iterator: public std::iterator<std::bidirectional_iterator_tag,
      size_t, std::ptrdiff_t, size_t*, size_t>
  {
  public:
    value_type operator*() const;

    Iterator& operator++();
    Iterator& operator--();

    Iterator operator++(int);
    Iterator operator--(int);

    bool operator==(const Iterator& iterator) const;
    bool operator!=(const Iterator& iterator) const;

  private:
    friend class FactorialContainer;
    Iterator(size_t maxPosition, size_t minPosition, size_t position, value_type value);

    size_t maxPosition;
    size_t minPosition;
    size_t position;
    value_type value;
  };

  using const_iterator = Iterator;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  FactorialContainer(size_t size = 0);

  const_iterator begin() const;
  const_iterator end() const;

  const_reverse_iterator rbegin() const;
  const_reverse_iterator rend() const;

private:
  size_t size;
  size_t maxValue;
};

#endif
