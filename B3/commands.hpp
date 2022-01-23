#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <string>

#include "phone-book.hpp"
#include "marks.hpp"

void add(PhoneBook& phonebook, Marks& marks, const std::string& name, const std::string& number);
void store(Marks& marks, std::ostream& out, const std::string& markName, const std::string& newMarkName);
void insertBefore(PhoneBook& phonebook, Marks& marks, std::ostream& out, const std::string& markName,
    const std::string& name, const std::string& number);
void insertAfter(PhoneBook& phonebook, Marks& marks, std::ostream& out, const std::string& markName,
    const std::string& name, const std::string& number);
void deleteRecord(PhoneBook& phonebook, Marks& marks, std::ostream& out, const std::string& markName);
void show(PhoneBook& phonebook, Marks& marks, std::ostream& out, const std::string& markName);
void moveOnStep(PhoneBook& phonebook, Marks& marks, std::ostream& out,
    const std::string& markName, const long int step);
void moveInPosition(PhoneBook& phonebook, Marks& marks, std::ostream& out,
    const std::string& markName, const std::string& position);
void printInvalidCommand(std::ostream& out);
void printInvalidBookmark(std::ostream& out);
void printEmpty(std::ostream& out);
void printInvalidStep(std::ostream& out);

#endif
