#include "commands.hpp"

#include <string>
#include <iostream>

#include "phone-book.hpp"
#include "marks.hpp"

void add(PhoneBook& phonebook, Marks& marks, const std::string& name, const std::string& number)
{
  marks.add(phonebook, name, number);
}

void store(Marks& marks, std::ostream& out, const std::string& markName, const std::string& newMarkName)
{
  marks.storeMark(markName, newMarkName, out);
}

void insertBefore(PhoneBook& phonebook, Marks& marks, std::ostream& out, const std::string& markName,
    const std::string& name, const std::string& number)
{
  marks.insertBefore(phonebook, markName, name, number, out);
}

void insertAfter(PhoneBook& phonebook, Marks& marks, std::ostream& out, const std::string& markName,
    const std::string& name, const std::string& number)
{
  marks.insertAfter(phonebook, markName, name, number, out);
}

void deleteRecord(PhoneBook& phonebook, Marks& marks, std::ostream& out, const std::string& markName)
{
  marks.deleteRecord(phonebook, markName, out);
}

void show(PhoneBook& phonebook, Marks& marks, std::ostream& out, const std::string& markName)
{
  marks.show(phonebook, markName, out);
}

void moveOnStep(PhoneBook& phonebook, Marks& marks, std::ostream& out,
    const std::string& markName, const long int step)
{
  marks.move(phonebook, markName, step, out);
}

void moveInPosition(PhoneBook& phonebook, Marks& marks, std::ostream& out,
    const std::string& markName, const std::string& position)
{
  marks.move(phonebook, markName, position, out);
}

void printInvalidCommand(std::ostream& out)
{
  out << "<INVALID COMMAND>\n";
}

void printInvalidBookmark(std::ostream& out)
{
  out << "<INVALID BOOKMARK>\n";
}

void printEmpty(std::ostream& out)
{
  out << "<EMPTY>\n";
}

void printInvalidStep(std::ostream& out)
{
  out << "<INVALID STEP>\n";
}
