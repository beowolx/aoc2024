#include "day07.h"
#include <vector>
#include <string>
#include <sstream>
#include <cstdint>

namespace
{
  bool is_possible_intermediate(int64_t current, int64_t target)
  {
    return current <= target;
  }

  int64_t fast_concatenate(int64_t left, int64_t right)
  {
    if (right == 0)
      return left * 10;

    int64_t multiplier = 1;
    int64_t temp = right;
    while (temp > 0)
    {
      multiplier *= 10;
      temp /= 10;
    }
    return left * multiplier + right;
  }

  bool parse_input_line(const std::string &line, int64_t &target, std::vector<int64_t> &numbers)
  {
    if (line.empty())
      return false;

    std::size_t colon_pos = line.find(':');
    if (colon_pos == std::string::npos)
      return false;

    target = std::stoll(line.substr(0, colon_pos));
    std::string numbers_part = line.substr(colon_pos + 1);

    std::istringstream iss(numbers_part);
    int64_t num;
    while (iss >> num)
    {
      numbers.push_back(num);
    }

    return !numbers.empty();
  }

  bool solve_part1(const std::vector<int64_t> &numbers,
                   size_t current_idx,
                   int64_t current_value,
                   int64_t target)
  {
    if (current_idx == numbers.size())
    {
      return current_value == target;
    }

    if (!is_possible_intermediate(current_value, target))
    {
      return false;
    }

    if (solve_part1(numbers, current_idx + 1,
                    current_value + numbers[current_idx], target))
    {
      return true;
    }

    int64_t mult_result = current_value * numbers[current_idx];
    if (mult_result <= target &&
        solve_part1(numbers, current_idx + 1, mult_result, target))
    {
      return true;
    }

    return false;
  }

  bool solve_part2(const std::vector<int64_t> &numbers,
                   size_t current_idx,
                   int64_t current_value,
                   int64_t target)
  {
    if (current_idx == numbers.size())
    {
      return current_value == target;
    }

    if (!is_possible_intermediate(current_value, target))
    {
      return false;
    }

    if (solve_part2(numbers, current_idx + 1,
                    current_value + numbers[current_idx], target))
    {
      return true;
    }

    int64_t mult_result = current_value * numbers[current_idx];
    if (mult_result <= target &&
        solve_part2(numbers, current_idx + 1, mult_result, target))
    {
      return true;
    }

    int64_t concat_result = fast_concatenate(current_value, numbers[current_idx]);
    if (concat_result <= target &&
        solve_part2(numbers, current_idx + 1, concat_result, target))
    {
      return true;
    }

    return false;
  }
}

int64_t day07_part1(const std::vector<std::string> &input)
{
  int64_t total_sum = 0;

  for (const auto &line : input)
  {
    int64_t target;
    std::vector<int64_t> numbers;

    if (!parse_input_line(line, target, numbers))
    {
      continue;
    }

    if (numbers.size() == 1)
    {
      if (numbers[0] == target)
      {
        total_sum += target;
      }
      continue;
    }

    if (solve_part1(numbers, 1, numbers[0], target))
    {
      total_sum += target;
    }
  }

  return total_sum;
}

int64_t day07_part2(const std::vector<std::string> &input)
{
  int64_t total_sum = 0;

  for (const auto &line : input)
  {
    int64_t target;
    std::vector<int64_t> numbers;

    if (!parse_input_line(line, target, numbers))
    {
      continue;
    }

    if (numbers.size() == 1)
    {
      if (numbers[0] == target)
      {
        total_sum += target;
      }
      continue;
    }

    if (solve_part2(numbers, 1, numbers[0], target))
    {
      total_sum += target;
    }
  }

  return total_sum;
}