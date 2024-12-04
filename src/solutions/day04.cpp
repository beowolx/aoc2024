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

int32_t day04_part2(const std::vector<std::string> &input)
{
  return 0;
}
