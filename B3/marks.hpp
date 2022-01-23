#ifndef MARKS_HPP
#define MARKS_HPP

#include <unordered_map>
#include <string>

#include "phone-book.hpp"

class Marks
{
public:
  Marks(PhoneBook& phonebook);
  void moveMarks(PhoneBook& phonebook);
  void add(PhoneBook& phonebook, const std::string& name, const std::string& number);
  void storeMark(const std::string& markName, const std::string& newMarkName, std::ostream& out);
  void insertBefore(PhoneBook& phonebook, const std::string& markName,
      const std::string& name, const std::string& number, std::ostream& out);
  void insertAfter(PhoneBook& phonebook, const std::string& markName,
      const std::string& name, const std::string& number, std::ostream& out);
  void deleteRecord(PhoneBook& phonebook, const std::string& markName, std::ostream& out);
  void show(const PhoneBook& phonebook, const std::string& markName, std::ostream& out) const;
  void move(PhoneBook& phonebook, const std::string& markName, const long int step, std::ostream& out);
  void move(PhoneBook& phonebook, const std::string& markName, const std::string& position, std::ostream& out);

private:
  std::unordered_map<std::string, PhoneBook::iterator> marks_;
};

#endif
