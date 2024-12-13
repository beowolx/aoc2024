#include "day13.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <cmath>

struct Machine
{
  int A_x, A_y;
  int B_x, B_y;
  int P_x, P_y;
};

int32_t day13_part1(const std::vector<std::string> &input)
{

  std::vector<Machine> machines;
  {
    Machine m;
    int line_count = 0;
    for (size_t i = 0; i < input.size(); ++i)
    {
      const std::string &line = input[i];
      if (line.empty())
      {
        if (line_count == 3)
        {
          machines.push_back(m);
        }
        line_count = 0;
        continue;
      }

      std::istringstream iss(line);
      std::string token;
      if (line.find("Button A:") != std::string::npos)
      {
        int A_x, A_y;
        size_t x_pos = line.find("X+");
        size_t y_pos = line.find("Y+");
        if (x_pos == std::string::npos || y_pos == std::string::npos)
          continue;
        {
          std::string x_sub = line.substr(x_pos + 2);
          size_t comma_pos = x_sub.find(',');
          if (comma_pos != std::string::npos)
          {
            x_sub = x_sub.substr(0, comma_pos);
          }
          A_x = std::stoi(x_sub);
        }
        {
          std::string y_sub = line.substr(y_pos + 2);
          A_y = std::stoi(y_sub);
        }
        m.A_x = A_x;
        m.A_y = A_y;
        line_count++;
      }
      else if (line.find("Button B:") != std::string::npos)
      {
        int B_x, B_y;
        size_t x_pos = line.find("X+");
        size_t y_pos = line.find("Y+");
        std::string x_sub = line.substr(x_pos + 2);
        size_t comma_pos = x_sub.find(',');
        if (comma_pos != std::string::npos)
        {
          x_sub = x_sub.substr(0, comma_pos);
        }
        B_x = std::stoi(x_sub);

        std::string y_sub = line.substr(y_pos + 2);
        B_y = std::stoi(y_sub);
        m.B_x = B_x;
        m.B_y = B_y;
        line_count++;
      }
      else if (line.find("Prize:") != std::string::npos)
      {
        int P_x, P_y;
        size_t x_pos = line.find("X=");
        size_t y_pos = line.find("Y=");
        {
          std::string x_sub = line.substr(x_pos + 2);
          size_t space_pos = x_sub.find(' ');
          if (space_pos != std::string::npos)
          {
            x_sub = x_sub.substr(0, space_pos);
          }
          P_x = std::stoi(x_sub);
        }
        {
          std::string y_sub = line.substr(y_pos + 2);
          P_y = std::stoi(y_sub);
        }
        m.P_x = P_x;
        m.P_y = P_y;
        line_count++;
      }
    }
    if (line_count == 3)
    {
      machines.push_back(m);
    }
  }

  int count_solved = 0;
  int32_t total_cost = 0;

  for (auto &mach : machines)
  {
    int best_cost = std::numeric_limits<int>::max();

    for (int a = 0; a <= 100; ++a)
    {
      int64_t x_rem = (int64_t)mach.P_x - (int64_t)mach.A_x * a;
      if (mach.B_x == 0)
      {
        if (x_rem != 0)
          continue;
        if (mach.B_y == 0)
        {
          if (mach.P_y == mach.A_y * a)
          {
            int cost = 3 * a;
            if (cost < best_cost)
              best_cost = cost;
          }
        }
        else
        {
          int64_t y_rem = (int64_t)mach.P_y - (int64_t)mach.A_y * a;
          if (y_rem % mach.B_y == 0)
          {
            int b = (int)(y_rem / mach.B_y);
            if (b >= 0 && b <= 100)
            {
              int cost = 3 * a + b;
              if (cost < best_cost)
                best_cost = cost;
            }
          }
        }
        continue;
      }

      if (x_rem % mach.B_x == 0)
      {
        int b = (int)(x_rem / mach.B_x);
        if (b < 0 || b > 100)
          continue;

        int64_t lhs_y = (int64_t)mach.A_y * a + (int64_t)mach.B_y * b;
        if (lhs_y == mach.P_y)
        {
          int cost = 3 * a + b;
          if (cost < best_cost)
          {
            best_cost = cost;
          }
        }
      }
    }

    if (best_cost < std::numeric_limits<int>::max())
    {
      count_solved++;
      total_cost += best_cost;
    }
  }

  return total_cost;
}

static int64_t safe_div(int64_t num, int64_t den)
{
  return num / den;
}

static bool solve_machine(const Machine &m, int64_t &best_cost)
{
  const int64_t OFFSET = 10000000000000LL;

  int64_t P_x = m.P_x + OFFSET;
  int64_t P_y = m.P_y + OFFSET;

  int64_t A_x = m.A_x, A_y = m.A_y;
  int64_t B_x = m.B_x, B_y = m.B_y;

  __int128 D = (__int128)A_x * B_y - (__int128)A_y * B_x;
  if (D == 0)
  {
    return false;
  }

  __int128 numerator_a = (__int128)P_x * B_y - (__int128)P_y * B_x;
  __int128 numerator_b = (__int128)P_y * A_x - (__int128)P_x * A_y;

  if (numerator_a % D != 0 || numerator_b % D != 0)
  {
    return false;
  }

  int64_t a0 = (int64_t)(numerator_a / D);
  int64_t b0 = (int64_t)(numerator_b / D);

  int64_t ByD = 0, AyD = 0;

  if (B_y % D == 0 && A_y % D == 0)
  {
    ByD = B_y / D;
    AyD = A_y / D;
  }
  else
  {
    if (a0 < 0 || b0 < 0)
      return false;
    int64_t cost = 3 * a0 + b0;
    if (cost < best_cost)
      best_cost = cost;
    return true;
  }

  double tmin = -std::numeric_limits<double>::infinity();
  double tmax = std::numeric_limits<double>::infinity();

  if (ByD != 0)
  {
    double bound = -(double)a0 / (double)ByD;
    if (ByD > 0)
    {
      if (bound > tmin)
        tmin = bound;
    }
    else
    {
      if (bound < tmax)
        tmax = bound;
    }
  }
  else
  {
    if (a0 < 0)
      return false;
  }

  if (AyD != 0)
  {
    double bound = (double)b0 / (double)AyD;
    if (AyD > 0)
    {
      if (bound < tmax)
        tmax = bound;
    }
    else
    {
      if (bound > tmin)
        tmin = bound;
    }
  }
  else
  {
    if (b0 < 0)
      return false;
  }

  __int128 cost_slope = 3 * (__int128)ByD - (__int128)AyD;
  __int128 base_cost = 3 * (__int128)a0 + (__int128)b0;

  double low_bound = std::ceil(tmin);
  double high_bound = std::floor(tmax);

  if (low_bound > high_bound)
  {
    if (ByD == 0 && AyD == 0 && a0 >= 0 && b0 >= 0)
    {
      int64_t cost = 3 * a0 + b0;
      if (cost < best_cost)
        best_cost = cost;
      return true;
    }
    return false;
  }

  int64_t chosen_t;
  if (cost_slope > 0)
    chosen_t = (int64_t)low_bound;
  else if (cost_slope < 0)
    chosen_t = (int64_t)high_bound;
  else
    chosen_t = (int64_t)low_bound;

  __int128 final_a = a0 + chosen_t * ByD;
  __int128 final_b = b0 - chosen_t * AyD;

  if (final_a < 0 || final_b < 0)
  {
    return false;
  }

  __int128 final_cost = 3 * final_a + final_b;
  if (final_cost < best_cost)
    best_cost = (int64_t)final_cost;

  return true;
}

int64_t day13_part2(const std::vector<std::string> &input)
{
  std::vector<Machine> machines;
  {
    Machine m;
    int line_count = 0;
    for (size_t i = 0; i < input.size(); ++i)
    {
      const std::string &line = input[i];
      if (line.empty())
      {
        if (line_count == 3)
        {
          machines.push_back(m);
        }
        line_count = 0;
        continue;
      }

      if (line.find("Button A:") != std::string::npos)
      {
        size_t x_pos = line.find("X+");
        size_t y_pos = line.find("Y+");
        std::string x_sub = line.substr(x_pos + 2, line.find(',') - (x_pos + 2));
        std::string y_sub = line.substr(y_pos + 2);
        m.A_x = std::stoll(x_sub);
        m.A_y = std::stoll(y_sub);
        line_count++;
      }
      else if (line.find("Button B:") != std::string::npos)
      {
        size_t x_pos = line.find("X+");
        size_t y_pos = line.find("Y+");
        std::string x_sub = line.substr(x_pos + 2, line.find(',', x_pos) - (x_pos + 2));
        std::string y_sub = line.substr(y_pos + 2);
        m.B_x = std::stoll(x_sub);
        m.B_y = std::stoll(y_sub);
        line_count++;
      }
      else if (line.find("Prize:") != std::string::npos)
      {
        size_t x_pos = line.find("X=");
        size_t y_pos = line.find("Y=");
        {
          std::string x_sub = line.substr(x_pos + 2);
          size_t space_pos = x_sub.find(' ');
          if (space_pos != std::string::npos)
            x_sub = x_sub.substr(0, space_pos);
          m.P_x = std::stoll(x_sub);
        }
        {
          std::string y_sub = line.substr(y_pos + 2);
          m.P_y = std::stoll(y_sub);
        }
        line_count++;
      }
    }
    if (line_count == 3)
    {
      machines.push_back(m);
    }
  }

  int count_solved = 0;
  int64_t total_cost = 0;
  for (auto &mach : machines)
  {
    int64_t best_cost = std::numeric_limits<int64_t>::max();
    bool res = solve_machine(mach, best_cost);
    if (res && best_cost < std::numeric_limits<int64_t>::max())
    {
      count_solved++;
      total_cost += best_cost;
    }
  }

  return total_cost;
}