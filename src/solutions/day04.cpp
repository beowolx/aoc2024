#include "day04.h"
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

const std::vector<std::pair<int, int>> directions = {
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
    {-1, -1}};

bool check_direction(const std::vector<std::string> &grid,
                     size_t row,
                     size_t col,
                     const std::pair<int, int> &direction)
{
  if (row + 3 * direction.first >= grid.size() ||
      row + 3 * direction.first < 0 ||
      col + 3 * direction.second >= grid[0].size() ||
      col + 3 * direction.second < 0)
  {
    return false;
  }

  return (grid[row][col] == 'X' &&
          grid[row + direction.first][col + direction.second] == 'M' &&
          grid[row + 2 * direction.first][col + 2 * direction.second] == 'A' &&
          grid[row + 3 * direction.first][col + 3 * direction.second] == 'S');
}

int32_t day04_part1(const std::vector<std::string> &input)
{
  int xmas_count = 0;

  for (size_t i = 0; i < input.size(); ++i)
  {
    for (size_t j = 0; j < input[0].size(); ++j)
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
                     size_t row,
                     size_t col)
{
  if (row == 0 || row >= grid.size() - 1 ||
      col == 0 || col >= grid[0].size() - 1)
  {
    return false;
  }

  if (grid[row][col] != 'A')
  {
    return false;
  }

  char up_left = grid[row - 1][col - 1];
  char up_right = grid[row - 1][col + 1];
  char down_left = grid[row + 1][col - 1];
  char down_right = grid[row + 1][col + 1];

  bool diagonal1_valid =
      ((up_left == 'M' && down_right == 'S') ||
       (up_left == 'S' && down_right == 'M')) &&
      ((up_right == 'M' && down_left == 'S') ||
       (up_right == 'S' && down_left == 'M'));

  bool diagonal2_valid =
      ((down_left == 'M' && up_right == 'S') ||
       (down_left == 'S' && up_right == 'M')) &&
      ((down_right == 'M' && up_left == 'S') ||
       (down_right == 'S' && up_left == 'M'));

  return diagonal1_valid || diagonal2_valid;
}

int32_t day04_part2(const std::vector<std::string> &input)
{
  int xmas_count = 0;

  for (size_t i = 1; i < input.size() - 1; ++i)
  {
    for (size_t j = 1; j < input[0].size() - 1; ++j)
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