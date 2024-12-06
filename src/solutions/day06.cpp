#include <vector>
#include <string>
#include <cstdint>
#include <iostream>

static const int drow[4] = {-1, 0, 1, 0};
static const int dcol[4] = {0, 1, 0, -1};

struct State
{
  int r, c, d;
};

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

bool simulate_with_extra_obstacle(std::vector<std::string> &map, int add_r, int add_c)
{
  int rows = (int)map.size();
  int cols = rows > 0 ? (int)map[0].size() : 0;

  char original_char = '.';
  if (add_r >= 0 && add_c >= 0)
  {
    original_char = map[add_r][add_c];
    map[add_r][add_c] = '#';
  }

  int guard_r = -1, guard_c = -1, dir = -1;
  for (int r = 0; r < rows; ++r)
  {
    for (int c = 0; c < cols; ++c)
    {
      char ch = map[r][c];
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

  std::vector<bool> visited_states(rows * cols * 4, false);
  auto state_index = [&](int rr, int cc, int dd)
  {
    return ((rr * cols) + cc) * 4 + dd;
  };

  visited_states[state_index(guard_r, guard_c, dir)] = true;

  bool loop_detected = false;
  while (true)
  {
    int nr = guard_r + drow[dir];
    int nc = guard_c + dcol[dir];

    bool blocked = false;
    if (nr < 0 || nr >= rows || nc < 0 || nc >= cols)
    {
      break;
    }

    if (map[nr][nc] == '#')
    {
      blocked = true;
    }

    if (blocked)
    {
      dir = (dir + 1) % 4;
      int idx = state_index(guard_r, guard_c, dir);
      if (visited_states[idx])
      {
        loop_detected = true;
        break;
      }
      visited_states[idx] = true;
    }
    else
    {
      guard_r = nr;
      guard_c = nc;
      int idx = state_index(guard_r, guard_c, dir);
      if (visited_states[idx])
      {
        loop_detected = true;
        break;
      }
      visited_states[idx] = true;
    }
  }

  if (add_r >= 0 && add_c >= 0)
  {
    map[add_r][add_c] = original_char;
  }

  return loop_detected;
}

int32_t day06_part2(const std::vector<std::string> &input)
{
  int rows = (int)input.size();
  if (rows == 0)
    return 0;
  int cols = (int)input[0].size();

  int guard_r = -1, guard_c = -1;
  for (int r = 0; r < rows; ++r)
  {
    for (int c = 0; c < cols; ++c)
    {
      char ch = input[r][c];
      if (ch == '^' || ch == '>' || ch == 'v' || ch == '<')
      {
        guard_r = r;
        guard_c = c;
      }
    }
  }

  std::vector<std::string> map = input;

  int32_t count = 0;

  for (int r = 0; r < rows; ++r)
  {
    for (int c = 0; c < cols; ++c)
    {
      if (r == guard_r && c == guard_c)
        continue;
      if (map[r][c] == '.')
      {
        bool loop = simulate_with_extra_obstacle(map, r, c);
        if (loop)
          count++;
      }
    }
  }

  return count;
}