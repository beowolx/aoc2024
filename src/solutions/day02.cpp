#include "day02.h"
#include <iostream>
#include <sstream>

std::vector<int> parse_line(const std::string &line)
{
  std::vector<int> numbers;
  std::istringstream iss(line);
  int number;
  while (iss >> number)
    numbers.push_back(number);
  return numbers;
}

bool is_safe(const std::vector<int> &levels)
{
  if (levels.size() < 2)
  {
    return false;
  }

  bool is_increasing = levels[1] > levels[0];

  for (size_t i = 1; i < levels.size(); ++i)
  {
    int diff = levels[i] - levels[i - 1];

    if (std::abs(diff) < 1 || std::abs(diff) > 3)
    {
      return false;
    }

    if (is_increasing && diff < 0)
    {
      return false;
    }
    if (!is_increasing && diff > 0)
    {
      return false;
    }
  }

  return true;
}

int32_t day02_part1(const std::vector<std::string> &input)
{
  int safe_count = 0;
  for (const auto &line : input)
  {
    std::vector<int> levels = parse_line(line);
    if (is_safe(levels))
    {
      safe_count++;
    }
  }
  return safe_count;
}