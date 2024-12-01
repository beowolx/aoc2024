#include "day01.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstdlib>

int32_t day01_part1(const std::vector<std::string> &input)
{
  std::vector<int> left_numbers;
  std::vector<int> right_numbers;
  left_numbers.reserve(input.size());
  right_numbers.reserve(input.size());

  for (const auto &line : input)
  {
    int left, right;
    std::istringstream iss(line);
    iss >> left >> right;
    left_numbers.push_back(left);
    right_numbers.push_back(right);
  }

  std::sort(left_numbers.begin(), left_numbers.end());
  std::sort(right_numbers.begin(), right_numbers.end());

  int32_t total_diff = 0;
  for (size_t i = 0; i < left_numbers.size(); ++i)
  {
    total_diff += std::abs(left_numbers[i] - right_numbers[i]);
  }

  return total_diff;
}

int32_t day01_part2(const std::vector<std::string> &input)
{
  return 0;
}