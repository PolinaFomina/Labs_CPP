#ifndef PARSER_HPP
#define PARSER_HPP

#include <functional>
#include <iostream>
#include <sstream>

#include "phone-book.hpp"
#include "marks.hpp"

using CommandType = std::function<void(PhoneBook&, Marks&, std::ostream&)>;

CommandType parse(std::istringstream& stream);
CommandType parseAdd(std::istringstream& stream);
CommandType parseStore(std::istringstream& stream);
CommandType parseInsert(std::istringstream& stream);
CommandType parseDelete(std::istringstream& stream);
CommandType parseShow(std::istringstream& stream);
CommandType parseMove(std::istringstream& stream);

#endif
