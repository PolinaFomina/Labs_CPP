#include "marks.hpp"

#include <iostream>
#include <stdexcept>
#include <iterator>
#include <sstream>

#include "commands.hpp"

Marks::Marks(PhoneBook& phonebook)
{
  marks_["current"] = phonebook.end();
}

void Marks::moveMarks(PhoneBook& phonebook)
{
  if (std::next(phonebook.begin()) == phonebook.end())
  {
    for (auto i = marks_.begin(); i != marks_.end(); i++)
    {
      i->second = phonebook.begin();
    }
  }
}

void Marks::add(PhoneBook& phonebook, const std::string& name, const std::string& number)
{
  phonebook.add(PhoneBook::record_t{ name, number });
  moveMarks(phonebook);
}

void Marks::storeMark(const std::string& markName, const std::string& newMarkName, std::ostream& out)
{
  if (markName.empty())
  {
    throw std::invalid_argument("Name of mark is absent");
  }
  if (newMarkName.empty())
  {
    throw std::invalid_argument("New name of mark is absent");
  }

  auto iterator = marks_.find(markName);
  if (iterator == marks_.end())
  {
    printInvalidBookmark(out);
  }
  else
  {
    marks_[newMarkName] = iterator->second;
  }
}

void Marks::insertBefore(PhoneBook& phonebook, const std::string& markName,
  const std::string& name, const std::string& number, std::ostream& out)
{
  if (markName.empty())
  {
    throw std::invalid_argument("Name of mark is absent");
  }

  auto iterator = marks_.find(markName);
  if (iterator == marks_.end())
  {
    printInvalidBookmark(out);
  }
  else
  {
    if (phonebook.empty())
    {
      add(phonebook, name, number);
    }
    else
    {
      phonebook.insertBefore(iterator->second, PhoneBook::record_t{ name, number });
    }
  }
}

void Marks::insertAfter(PhoneBook& phonebook, const std::string& markName,
    const std::string& name, const std::string& number, std::ostream& out)
{
  if (markName.empty())
  {
    throw std::invalid_argument("Name of mark is absent");
  }

  auto iterator = marks_.find(markName);
  if (iterator == marks_.end())
  {
    printInvalidBookmark(out);
  }
  else
  {
    if (phonebook.empty())
    {
      add(phonebook, name, number);
    }
    else
    {
      phonebook.insertAfter(iterator->second, PhoneBook::record_t{ name, number });
    }
  }
}

void Marks::deleteRecord(PhoneBook& phonebook, const std::string& markName, std::ostream& out)
{
  auto iterator = marks_.find(markName);
  if (iterator == marks_.end())
  {
    printInvalidBookmark(out);
    return;
  }
  if (iterator->second == phonebook.end())
  {
    printEmpty(out);
    return;
  }

  for (auto i = marks_.begin(); i != marks_.end(); i++)
  {
    if ((i->second == iterator->second) && (i != iterator))
    {
      if ((i->second != std::prev(phonebook.end())) || (i->second == phonebook.begin()))
      {
        i->second++;
      }
      else
      {
        i->second--;
      }
    }
  }

  if ((iterator->second != std::prev(phonebook.end())) || (iterator->second == phonebook.begin()))
  {
    marks_[markName] = phonebook.remove(iterator->second);
  }
  else
  {
    marks_[markName] = std::prev(phonebook.remove(iterator->second));
  }
}

void Marks::show(const PhoneBook& phonebook, const std::string& markName, std::ostream& out) const
{
  if (markName.empty())
  {
    throw std::invalid_argument("Name of mark is absent");
  }

  auto iterator = marks_.find(markName);
  if (iterator == marks_.end())
  {
    printInvalidBookmark(out);
  }
  else if (phonebook.empty())
  {
    printEmpty(out);
  }
  else
  {
    out << iterator->second->number << " " << iterator->second->name << "\n";
  }
}

void Marks::move(PhoneBook& phonebook, const std::string& markName, const long int step, std::ostream& out)
{
  if (markName.empty())
  {
    throw std::invalid_argument("Name of mark is absent");
  }

  auto iterator = marks_.find(markName);
  if (iterator == marks_.end())
  {
    printInvalidBookmark(out);
    return;
  }

  if (step > 0)
  {
    if (std::distance(iterator->second, --phonebook.end()) < step)
    {
      iterator->second = --phonebook.end();
    }
    iterator->second = std::next(iterator->second, step);
  }
  else
  {
    if (std::distance(phonebook.begin(), iterator->second) < -step)
    {
      iterator->second = phonebook.begin();
    }
    iterator->second = std::prev(iterator->second, -step);
  }
}

void Marks::move(PhoneBook& phonebook, const std::string& markName, const std::string& position, std::ostream& out)
{
  if (markName.empty())
  {
    throw std::invalid_argument("Name of mark is absent");
  }
  if (position.empty())
  {
    throw std::invalid_argument("Position is absent");
  }

  auto iterator1 = marks_.find(markName);
  if (iterator1 == marks_.end())
  {
    printInvalidBookmark(out);
    return;
  }

  const std::unordered_map<std::string, PhoneBook::iterator> positions
  {
    {"first", phonebook.begin()},
    {"last", std::prev(phonebook.end())}
  };

  auto iterator2 = positions.find(position);
  if (iterator2 == positions.end())
  {
    printInvalidStep(out);
    return;
  }

  iterator1->second = iterator2->second;
}
