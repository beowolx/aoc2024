#include <cstdint>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <deque>
#include <cmath>
#include <unordered_map>
#include <iostream>
#include "day11.h"

size_t count_digits(uint64_t n)
{
  if (n == 0)
    return 1;
  return static_cast<size_t>(std::log10(n)) + 1;
}

std::pair<uint64_t, uint64_t> split_number(uint64_t n)
{
  size_t digits = count_digits(n);
  size_t half = digits / 2;
  uint64_t divisor = static_cast<uint64_t>(std::pow(10, half));
  return {n / divisor, n % divisor};
}

class Stone
{
public:
  explicit Stone(uint64_t value) : number(value) {}

  size_t transform_count() const
  {
    if (number == 0)
      return 1;
    size_t digits = count_digits(number);
    return (digits % 2 == 0) ? 2 : 1;
  }

  std::vector<Stone> transform() const
  {
    std::vector<Stone> result;

    if (number == 0)
    {
      result.emplace_back(1);
      return result;
    }

    size_t digits = count_digits(number);
    if (digits % 2 == 0)
    {
      auto [left, right] = split_number(number);
      result.emplace_back(left);
      result.emplace_back(right);
      return result;
    }

    result.emplace_back(number * 2024);
    return result;
  }

private:
  uint64_t number;
};

int32_t day11_part1(const std::vector<std::string> &input)
{
  std::deque<Stone> stones;
  std::string number_str;
  std::istringstream iss(input[0]);

  while (iss >> number_str)
  {
    stones.emplace_back(std::stoull(number_str));
  }

  for (int blink = 0; blink < 25; ++blink)
  {
    size_t current_size = stones.size();

    for (size_t i = 0; i < current_size; ++i)
    {
      Stone current = stones.front();
      stones.pop_front();

      auto transformed = current.transform();
      for (const auto &new_stone : transformed)
      {
        stones.push_back(new_stone);
      }
    }
  }

  return stones.size();
}

struct Key
{
  std::string stone;
  int steps;
  bool operator==(const Key &o) const
  {
    return steps == o.steps && stone == o.stone;
  }
};

struct KeyHash
{
  std::size_t operator()(const Key &k) const
  {
    std::hash<std::string> h;
    return h(k.stone) ^ (std::hash<int>()(k.steps) << 1);
  }
};

static std::string trim_zeros(const std::string &num)
{
  size_t i = 0;
  while (i < num.size() && num[i] == '0')
    i++;
  return (i == num.size()) ? "0" : num.substr(i);
}

static std::string mul2024(const std::string &num)
{
  int m = 2024;
  int carry = 0;
  std::string res;
  res.reserve(num.size() + 5);
  for (int i = (int)num.size() - 1; i >= 0; i--)
  {
    int d = num[i] - '0';
    long long prod = (long long)d * m + carry;
    carry = (int)(prod / 10);
    int r = (int)(prod % 10);
    res.push_back((char)('0' + r));
  }
  while (carry > 0)
  {
    int r = carry % 10;
    carry /= 10;
    res.push_back((char)('0' + r));
  }
  std::reverse(res.begin(), res.end());
  return res;
}

static std::string big_add_str(const std::string &A, const std::string &B)
{
  int i = (int)A.size() - 1, j = (int)B.size() - 1;
  int carry = 0;
  std::string R;
  while (i >= 0 || j >= 0 || carry > 0)
  {
    int x = 0;
    if (i >= 0)
      x += A[i--] - '0';
    if (j >= 0)
      x += B[j--] - '0';
    x += carry;
    carry = x / 10;
    x %= 10;
    R.push_back((char)('0' + x));
  }
  std::reverse(R.begin(), R.end());
  return R;
}

static std::string add_counts(const std::string &a, const std::string &b)
{
  if (a == "0")
    return b;
  if (b == "0")
    return a;
  return big_add_str(a, b);
}

static std::unordered_map<Key, std::string, KeyHash> memo;

static std::string handle_once(const std::string &stone)
{
  if (stone == "0")
    return "1#";
  int len = (int)stone.size();
  if (len % 2 == 0)
  {
    int half = len / 2;
    std::string L = trim_zeros(stone.substr(0, half));
    std::string R = trim_zeros(stone.substr(half));
    return L + "#" + R + "#";
  }
  else
  {
    std::string M = mul2024(stone);
    return M + "#";
  }
}

static std::string get_count(std::string stone, int steps);

static std::string get_count(std::string stone, int steps)
{
  if (steps == 0)
    return "1";
  Key k = {stone, steps};
  auto it = memo.find(k);
  if (it != memo.end())
    return it->second;

  std::string after = handle_once(stone);
  std::vector<std::string> nxt;
  {
    size_t start = 0;
    while (true)
    {
      size_t pos = after.find('#', start);
      if (pos == std::string::npos)
      {
        std::string part = after.substr(start);
        if (!part.empty())
          nxt.push_back(part);
        break;
      }
      else
      {
        std::string part = after.substr(start, pos - start);
        if (!part.empty())
          nxt.push_back(part);
        start = pos + 1;
      }
    }
  }

  std::string res = "0";
  for (auto &s : nxt)
  {
    res = add_counts(res, get_count(s, steps - 1));
  }
  memo[k] = res;
  return res;
}

int64_t day11_part2(const std::vector<std::string> &input)
{
  std::string total = "0";
  int steps = 75;
  if (!input.empty())
  {
    std::istringstream iss(input[0]);
    std::string st;
    while (iss >> st)
    {
      total = add_counts(total, get_count(st, steps));
    }
  }

  return std::stoull(total);
}
