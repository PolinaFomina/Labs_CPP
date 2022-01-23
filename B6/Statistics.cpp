#include "Statistics.hpp"

#include <algorithm>
#include <iostream>

Statistics::Statistics():
  maxNumber(0),
  minNumber(0),
  countOfNumbers(0),
  countPositiveNumbers(0),
  countNegativeNumbers(0),
  sumOfOdd(0),
  sumOfEven(0),
  first(0),
  isFirstLastEqual(false)
{}

void Statistics::operator()(const long long int number)
{
  if (!countOfNumbers)
  {
    maxNumber = number;
    minNumber = number;
    first = number;
  }

  maxNumber = std::max(number, maxNumber);
  minNumber = std::min(number, minNumber);

  countOfNumbers++;

  if (number > 0)
  {
    countPositiveNumbers++;
  }

  if (number < 0)
  {
    countNegativeNumbers++;
  }

  if (number % 2 != 0)
  {
    sumOfOdd += number;
  }
  else
  {
    sumOfEven += number;
  }

  isFirstLastEqual = (first == number);
}

std::ostream& operator<<(std::ostream& out, const Statistics& statistics)
{
  std::ostream::sentry sentry(out);
  if (sentry)
  {
    if (statistics.countOfNumbers)
    {
      out << "Max: " << statistics.maxNumber << '\n'
          << "Min: " << statistics.minNumber << '\n'
          << "Mean: " << static_cast<double> (statistics.sumOfOdd + statistics.sumOfEven)
              / static_cast<double> (statistics.countOfNumbers) << '\n'
          << "Positive: " << statistics.countPositiveNumbers << '\n'
          << "Negative: " << statistics.countNegativeNumbers << '\n'
          << "Odd Sum: " << statistics.sumOfOdd << '\n'
          << "Even Sum: " << statistics.sumOfEven << '\n'
          << "First/Last Equal: " << (statistics.isFirstLastEqual ? "yes" : "no") << '\n';
    }
    else
    {
      out << "No Data\n";
    }
  }

  return out;
}
