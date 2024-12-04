#include "day04.h"
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <array>

constexpr std::array<std::pair<int, int>, 8> directions = {{
    // down
    {1, 0},
    // right
    {0, 1},
    // up
    {-1, 0},
    // left
    {0, -1},
    // down-right diagonal
    {1, 1},
    // down-left diagonal
    {1, -1},
    // up-right diagonal
    {-1, 1},
    // up-left diagonal
    {-1, -1},
}};

bool check_direction(const std::vector<std::string> &grid,
                     const int row,
                     const int col,
                     const std::pair<int, int> &direction)
{
  const int target_row = row + 3 * direction.first;
  const int target_col = col + 3 * direction.second;

  if (target_row >= grid.size() || target_col >= grid[0].size())
    return false;

  const std::string &row_data = grid[row];

  return (row_data[col] == 'X' &&
          grid[row + direction.first][col + direction.second] == 'M' &&
          grid[row + 2 * direction.first][col + 2 * direction.second] == 'A' &&
          grid[row + 3 * direction.first][col + 3 * direction.second] == 'S');
}

int32_t day04_part1(const std::vector<std::string> &input)
{
  int xmas_count = 0;

  for (int i = 0; i < input.size(); ++i)
  {
    for (int j = 0; j < input[0].size(); ++j)
    {
      if (input[i][j] == 'X')
      {
        for (const auto &direction : directions)
        {
          if (check_direction(input, i, j, direction))
          {
            xmas_count++;
          }
        }
      }
    }
  }

  return xmas_count;
}

bool check_x_pattern(const std::vector<std::string> &grid,
                     const int row,
                     const int col)
{
  if (grid[row][col] != 'A')
    return false;

  if (row == 0 || row >= grid.size() - 1 ||
      col == 0 || col >= grid[0].size() - 1)
    return false;

  const char up_left = grid[row - 1][col - 1];
  const char up_right = grid[row - 1][col + 1];
  const char down_left = grid[row + 1][col - 1];
  const char down_right = grid[row + 1][col + 1];

  const auto is_mas_pattern = [](char c1, char c2)
  {
    return (c1 == 'M' && c2 == 'S') || (c1 == 'S' && c2 == 'M');
  };

  return (is_mas_pattern(up_left, down_right) && is_mas_pattern(up_right, down_left)) ||
         (is_mas_pattern(down_left, up_right) && is_mas_pattern(down_right, up_left));
}

int32_t day04_part2(const std::vector<std::string> &input)
{
  int xmas_count = 0;

  for (int i = 1; i < input.size() - 1; ++i)
  {
    for (int j = 1; j < input[0].size() - 1; ++j)
    {
      if (input[i][j] == 'A')
      {
        if (check_x_pattern(input, i, j))
        {
          xmas_count++;
        }
      }
    }
  }

  return xmas_count;
}