#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <list>
#include <stdexcept>

template <typename QueueElement>
class QueueWithPriority
{
public:
  enum ElementPriority
  {
    LOW,
    NORMAL,
    HIGH
  };

  bool isEmpty() const;
  void put(const QueueElement& element, ElementPriority priority);
  void get(QueueElement& out);
  void accelerate();

private:
  std::list<QueueElement> priorities[3];
};

template <typename QueueElement>
bool QueueWithPriority<QueueElement>::isEmpty() const
{
  for (size_t i = 0; i < sizeof(priorities) / sizeof(priorities[0]); i++)
  {
    if (!priorities[i].empty())
    {
      return false;
    }
  }
  return true;
}

template <typename QueueElement>
void QueueWithPriority<QueueElement>::put(const QueueElement& element,
    ElementPriority priority)
{
  if ((priority < 0) || (priority >= sizeof(priorities) / sizeof(priorities[0])))
  {
    throw std::invalid_argument("Incorrect priority");
  }
  priorities[priority].push_back(element);
}

template <typename QueueElement>
void QueueWithPriority<QueueElement>::get(QueueElement& out)
{
  for (size_t i = (sizeof(priorities) / sizeof(priorities[0]) - 1); i >= 0; i--)
  {
    if (!priorities[i].empty())
    {
      out = priorities[i].front();
      priorities[i].pop_front();
      return;
    }
  }
  throw std::logic_error("Can't get an element from empty queue");
}

template <typename QueueElement>
void QueueWithPriority<QueueElement>::accelerate()
{
  priorities[2].splice(priorities[2].end(), priorities[0]);
}

#endif
