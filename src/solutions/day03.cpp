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
  int64_t total_sum = 0;
  const std::string mul_pattern = "mul(";
  const std::string do_pattern = "do()";
  const std::string dont_pattern = "don't()";

  bool mul_enabled = true;

  for (const auto &line : input)
  {
    size_t pos = 0;
    while (pos < line.size())
    {
      size_t pos_mul = line.find(mul_pattern, pos);
      size_t pos_do = line.find(do_pattern, pos);
      size_t pos_dont = line.find(dont_pattern, pos);

      size_t next_pos = std::string::npos;
      std::string matched_pattern;
      size_t pattern_length = 0;

      if (pos_mul != std::string::npos && (next_pos == std::string::npos || pos_mul < next_pos))
      {
        next_pos = pos_mul;
        matched_pattern = "mul";
        pattern_length = mul_pattern.size();
      }

      if (pos_do != std::string::npos && (next_pos == std::string::npos || pos_do < next_pos))
      {
        next_pos = pos_do;
        matched_pattern = "do";
        pattern_length = do_pattern.size();
      }

      if (pos_dont != std::string::npos && (next_pos == std::string::npos || pos_dont < next_pos))
      {
        next_pos = pos_dont;
        matched_pattern = "dont";
        pattern_length = dont_pattern.size();
      }

      if (next_pos == std::string::npos)
      {
        break;
      }

      if (matched_pattern == "mul")
      {
        if (mul_enabled)
        {
          total_sum += check_multiplication(line, next_pos + pattern_length);
        }
        pos = next_pos + 1;
      }
      else if (matched_pattern == "do")
      {
        mul_enabled = true;
        pos = next_pos + pattern_length;
      }
      else if (matched_pattern == "dont")
      {
        mul_enabled = false;
        pos = next_pos + pattern_length;
      }
    }
  }

  return static_cast<int32_t>(total_sum);
}