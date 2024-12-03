#include "day03.h"
#include <iostream>
#include <sstream>
#include <string>
#include <ranges>

int64_t check_multiplication(const std::string &line, size_t start_pos)
{
  static const std::string digits = "0123456789";

  size_t comma_pos = line.find_first_not_of(digits, start_pos);

  if (comma_pos == start_pos ||
      comma_pos == std::string::npos ||
      line[comma_pos] != ',')
  {
    return 0;
  }

  size_t end_pos = line.find_first_not_of(digits, comma_pos + 1);

  if (end_pos == comma_pos + 1 ||
      end_pos == std::string::npos ||
      line[end_pos] != ')')
  {
    return 0;
  }

  int first_num = std::stoi(line.substr(start_pos, comma_pos - start_pos));
  int second_num = std::stoi(line.substr(comma_pos + 1, end_pos - (comma_pos + 1)));

  return static_cast<int64_t>(first_num) * second_num;
}

int32_t day03_part1(const std::vector<std::string> &input)
{
  int64_t total_sum = 0;

  const std::string mul_pattern = "mul(";

  for (const auto &line : input)
  {
    size_t pos = 0;
    while ((pos = line.find(mul_pattern, pos)) != std::string::npos)
    {
      total_sum += check_multiplication(line, pos + 4);
      pos += 1;
    }
  }

  return static_cast<int32_t>(total_sum);
}

int32_t day03_part2(const std::vector<std::string> &input)
{
  return 0;
}