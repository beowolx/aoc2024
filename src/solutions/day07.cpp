#include "day07.h"
#include <vector>
#include <string>
#include <sstream>
#include <unordered_set>
#include <cstdint>

int64_t day07_part1(const std::vector<std::string> &input)
{
  int64_t total_sum = 0;

  for (const auto &line : input)
  {
    if (line.empty())
    {
      continue;
    }

    std::size_t colon_pos = line.find(':');
    if (colon_pos == std::string::npos)
    {
      continue;
    }

    int64_t target = std::stoll(line.substr(0, colon_pos));
    std::string numbers_part = line.substr(colon_pos + 1);

    std::vector<int64_t> numbers;
    {
      std::istringstream iss(numbers_part);
      int64_t num;
      while (iss >> num)
      {
        numbers.push_back(num);
      }
    }

    if (numbers.empty())
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

    std::unordered_set<int64_t> current_results;
    current_results.insert(numbers[0]);

    for (size_t i = 1; i < numbers.size(); ++i)
    {
      std::unordered_set<int64_t> new_results;
      for (auto val : current_results)
      {
        new_results.insert(val + numbers[i]);
        new_results.insert(val * numbers[i]);
      }
      current_results.swap(new_results);
    }

    if (current_results.find(target) != current_results.end())
    {
      total_sum += target;
    }
  }

  return total_sum;
}

static int64_t concatenate_result(int64_t left, int64_t right)
{
  std::string l = std::to_string(left);
  std::string r = std::to_string(right);
  return std::stoll(l + r);
}

int64_t day07_part2(const std::vector<std::string> &input)
{
  int64_t total_sum = 0;

  for (const auto &line : input)
  {
    if (line.empty())
    {
      continue;
    }

    std::size_t colon_pos = line.find(':');
    if (colon_pos == std::string::npos)
    {
      continue;
    }

    int64_t target = std::stoll(line.substr(0, colon_pos));
    std::string numbers_part = line.substr(colon_pos + 1);

    std::vector<int64_t> numbers;
    {
      std::istringstream iss(numbers_part);
      int64_t num;
      while (iss >> num)
      {
        numbers.push_back(num);
      }
    }

    if (numbers.empty())
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

    std::unordered_set<int64_t> current_results;
    current_results.insert(numbers[0]);

    for (size_t i = 1; i < numbers.size(); ++i)
    {
      std::unordered_set<int64_t> new_results;
      for (auto val : current_results)
      {
        new_results.insert(val + numbers[i]);
        new_results.insert(val * numbers[i]);
        new_results.insert(concatenate_result(val, numbers[i]));
      }
      current_results.swap(new_results);
    }

    if (current_results.find(target) != current_results.end())
    {
      total_sum += target;
    }
  }

  return total_sum;
}