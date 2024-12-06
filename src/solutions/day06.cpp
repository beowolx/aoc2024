#include <vector>
#include <string>
#include <cstdint>
#include <unordered_set>
#include <utility>
#include <iostream>

static const int drow[4] = {-1, 0, 1, 0};
static const int dcol[4] = {0, 1, 0, -1};

int32_t day06_part1(const std::vector<std::string> &input)
{

  int rows = (int)input.size();
  if (rows == 0)
    return 0;
  int cols = (int)input[0].size();

  int guard_r = -1, guard_c = -1, dir = -1;
  for (int r = 0; r < rows; ++r)
  {
    for (int c = 0; c < cols; ++c)
    {
      char ch = input[r][c];
      if (ch == '^')
      {
        guard_r = r;
        guard_c = c;
        dir = 0;
      }
      else if (ch == '>')
      {
        guard_r = r;
        guard_c = c;
        dir = 1;
      }
      else if (ch == 'v')
      {
        guard_r = r;
        guard_c = c;
        dir = 2;
      }
      else if (ch == '<')
      {
        guard_r = r;
        guard_c = c;
        dir = 3;
      }
    }
  }

  std::vector<bool> visited(rows * cols, false);
  auto mark_visited = [&](int rr, int cc)
  {
    visited[rr * cols + cc] = true;
  };
  auto is_visited = [&](int rr, int cc)
  {
    return visited[rr * cols + cc];
  };

  mark_visited(guard_r, guard_c);

  while (true)
  {
    int nr = guard_r + drow[dir];
    int nc = guard_c + dcol[dir];

    bool blocked = false;
    if (nr < 0 || nr >= rows || nc < 0 || nc >= cols)
    {
      break;
    }

    if (input[nr][nc] == '#')
    {
      blocked = true;
    }

    if (blocked)
    {
      dir = (dir + 1) % 4;
      continue;
    }
    else
    {
      guard_r = nr;
      guard_c = nc;
      if (!is_visited(guard_r, guard_c))
      {
        mark_visited(guard_r, guard_c);
      }
    }
  }

  int32_t count = 0;
  for (auto v : visited)
    if (v)
      count++;
  return count;
}

int32_t day06_part2(const std::vector<std::string> &input)
{
  return 0;
}