#include "day05.h"
#include <algorithm>
#include <sstream>
#include <utility>
#include <unordered_map>

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

void add_rule_to_map(std::unordered_map<int, std::vector<int>> &rules_map,
                     const std::pair<int, int> &rule)
{
  rules_map[rule.first].push_back(rule.second);
}

bool must_come_after(int number1, int number2,
                     const std::unordered_map<int, std::vector<int>> &rules_map)
{
  auto it = rules_map.find(number1);
  if (it != rules_map.end())
  {
    return std::find(it->second.begin(), it->second.end(), number2) != it->second.end();
  }
  return false;
}

bool compare_numbers(int n1, int n2,
                     const std::unordered_map<int, std::vector<int>> &rules_map)
{
  if (must_come_after(n1, n2, rules_map))
    return true;
  if (must_come_after(n2, n1, rules_map))
    return false;
  return n1 < n2;
}

int32_t day05_part2(const std::vector<std::string> &input)
{
  std::unordered_map<int, std::vector<int>> rules_map;
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
      auto rule = parse_rule(line);
      add_rule_to_map(rules_map, rule);
    }
    else
    {
      updates.push_back(parse_update(line));
    }
  }

  int32_t sum = 0;

  for (auto &update : updates)
  {
    bool is_valid = true;

    for (size_t i = 0; i < update.size() && is_valid; ++i)
    {
      for (size_t j = i + 1; j < update.size() && is_valid; ++j)
      {
        if (must_come_after(update[j], update[i], rules_map))
        {
          is_valid = false;
        }
      }
    }

    if (!is_valid)
    {
      std::sort(update.begin(), update.end(),
                [&rules_map](int n1, int n2)
                {
                  return compare_numbers(n1, n2, rules_map);
                });
      sum += update[update.size() / 2];
    }
  }

  return sum;
}