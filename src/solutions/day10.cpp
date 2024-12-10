#include "day10.h"
#include <vector>
#include <string>
#include <cstdint>
#include <iostream>

int32_t day10_part1(const std::vector<std::string> &input)
{

  int rows = (int)input.size();
  if (rows == 0)
  {
    return 0;
  }
  int cols = (int)input[0].size();

  std::vector<std::vector<int>> heightmap(rows, std::vector<int>(cols, 0));
  for (int r = 0; r < rows; r++)
  {
    for (int c = 0; c < cols; c++)
    {
      heightmap[r][c] = input[r][c] - '0';
    }
  }

  const int dr[4] = {-1, 1, 0, 0};
  const int dc[4] = {0, 0, -1, 1};

  std::vector<std::pair<int, int>> nines;
  for (int r = 0; r < rows; r++)
  {
    for (int c = 0; c < cols; c++)
    {
      if (heightmap[r][c] == 9)
      {
        nines.push_back({r, c});
      }
    }
  }
  int nine_count = (int)nines.size();

  std::vector<std::vector<std::vector<bool>>> reachable(rows, std::vector<std::vector<bool>>(cols, std::vector<bool>(nine_count, false)));

  std::vector<std::vector<int>> nine_id_map(rows, std::vector<int>(cols, -1));
  for (int i = 0; i < nine_count; i++)
  {
    nine_id_map[nines[i].first][nines[i].second] = i;
  }

  for (int r = 0; r < rows; r++)
  {
    for (int c = 0; c < cols; c++)
    {
      if (heightmap[r][c] == 9)
      {
        int id = nine_id_map[r][c];
        reachable[r][c][id] = true;
      }
    }
  }

  for (int h = 8; h >= 0; h--)
  {
    for (int r = 0; r < rows; r++)
    {
      for (int c = 0; c < cols; c++)
      {
        if (heightmap[r][c] == h)
        {
          for (int k = 0; k < 4; k++)
          {
            int nr = r + dr[k];
            int nc = c + dc[k];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols)
              continue;
            if (heightmap[nr][nc] == h + 1)
            {
              // Union reachable sets
              for (int idx = 0; idx < nine_count; idx++)
              {
                if (reachable[nr][nc][idx])
                {
                  reachable[r][c][idx] = true;
                }
              }
            }
          }
        }
      }
    }
  }

  int32_t total_score = 0;
  for (int r = 0; r < rows; r++)
  {
    for (int c = 0; c < cols; c++)
    {
      if (heightmap[r][c] == 0)
      {
        int count = 0;
        for (int idx = 0; idx < nine_count; idx++)
        {
          if (reachable[r][c][idx])
          {
            count++;
          }
        }
        total_score += count;
      }
    }
  }

  return total_score;
}

int32_t day10_part2(const std::vector<std::string> &input)
{
  return 0;
}