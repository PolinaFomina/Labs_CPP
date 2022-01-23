#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <list>
#include <string>

class PhoneBook
{
public:
  struct record_t
  {
    std::string name;
    std::string number;
  };

  using iterator = std::list<record_t>::iterator;
  using const_iterator = std::list<record_t>::const_iterator;

  void insertAfter(iterator iterator, const record_t& record);
  void insertBefore(iterator iterator, const record_t& record);
  void add(const record_t& record);
  iterator remove(iterator iterator);
  bool empty() const;
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

private:
  std::list<record_t> book_;
};

#endif
