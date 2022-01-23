#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <iostream>

class Statistics
{
public:
  Statistics();
  void operator()(const long long int number);
  friend std::ostream& operator<<(std::ostream& out, const Statistics& statistics);
private:
  long long int maxNumber, minNumber, countOfNumbers, countPositiveNumbers,
      countNegativeNumbers, sumOfOdd, sumOfEven, first;
  bool isFirstLastEqual;
};

#endif
