#include "day05.h"
#include <algorithm>
#include <sstream>
#include <utility>

std::pair<int, int> parse_rule(const std::string &line)
{
  size_t separator_pos = line.find('|');
  if (separator_pos == std::string::npos)
  {
    return {0, 0};
  }

  int first = std::stoi(line.substr(0, separator_pos));
  int second = std::stoi(line.substr(separator_pos + 1));
  return {first, second};
}

std::vector<int> parse_update(const std::string &line)
{
  std::vector<int> numbers;
  std::istringstream iss(line);
  std::string number_str;

  while (std::getline(iss, number_str, ','))
  {
    numbers.push_back(std::stoi(number_str));
  }

  return numbers;
}

bool is_valid_update(const std::vector<int> &update,
                     const std::vector<std::pair<int, int>> &rules)
{
  for (const auto &rule : rules)
  {
    auto it_first = std::find(update.begin(), update.end(), rule.first);
    auto it_second = std::find(update.begin(), update.end(), rule.second);

    if (it_first != update.end() && it_second != update.end())
    {
      if (it_second < it_first)
      {
        return false;
      }
    }
  }
  return true;
}

int32_t day05_part1(const std::vector<std::string> &input)
{
  std::vector<std::pair<int, int>> rules;
  std::vector<std::vector<int>> updates;
  bool parsing_rules = true;

  for (const auto &line : input)
  {
    if (line.empty())
    {
      parsing_rules = false;
      continue;
    }

    if (parsing_rules)
    {
      rules.push_back(parse_rule(line));
    }
    else
    {
      updates.push_back(parse_update(line));
    }
  }

  int32_t sum = 0;
  for (const auto &update : updates)
  {
    if (is_valid_update(update, rules))
    {
      sum += update[update.size() / 2];
    }
  }

  return sum;
}

int32_t day05_part2(const std::vector<std::string> &input)
{
  return 0;
}