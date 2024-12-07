#include <vector>
#include <string>
#include <cstdint>
#include <iostream>

static const int drow[4] = {-1, 0, 1, 0};
static const int dcol[4] = {0, 1, 0, -1};

inline int state_index(int r, int c, int d, int cols)
{
  return ((r * cols) + c) * 4 + d;
}

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
  visited[guard_r * cols + guard_c] = true;

  int r = guard_r, c = guard_c, d = dir;
  while (true)
  {
    int nr = r + drow[d];
    int nc = c + dcol[d];
    if (nr < 0 || nr >= rows || nc < 0 || nc >= cols)
      break;
    if (input[nr][nc] == '#')
    {
      d = (d + 1) % 4;
    }
    else
    {
      r = nr;
      c = nc;
      visited[r * cols + c] = true;
    }
  }

  int32_t count = 0;
  for (auto v : visited)
    if (v)
      count++;
  return count;
}

bool simulate_with_extra_obstacle(std::vector<std::string> &map,
                                  int add_r, int add_c,
                                  int guard_r_init, int guard_c_init, int dir_init,
                                  std::vector<bool> &visited_states,
                                  int rows, int cols)
{
  char original_char = '.';
  bool placing = (add_r >= 0 && add_c >= 0);
  if (placing)
  {
    original_char = map[add_r][add_c];
    map[add_r][add_c] = '#';
  }

  int guard_r = guard_r_init;
  int guard_c = guard_c_init;
  int d = dir_init;

  std::fill(visited_states.begin(), visited_states.end(), false);
  visited_states[state_index(guard_r, guard_c, d, cols)] = true;

  while (true)
  {
    int nr = guard_r + drow[d];
    int nc = guard_c + dcol[d];

    bool blocked = false;
    if (nr < 0 || nr >= rows || nc < 0 || nc >= cols)
    {
      break;
    }
    if (map[nr][nc] == '#')
      blocked = true;

    if (blocked)
    {
      d = (d + 1) % 4;
      int idx = state_index(guard_r, guard_c, d, cols);
      if (visited_states[idx])
      {
        if (placing)
          map[add_r][add_c] = original_char;
        return true;
      }
      visited_states[idx] = true;
    }
    else
    {
      guard_r = nr;
      guard_c = nc;
      int idx = state_index(guard_r, guard_c, d, cols);
      if (visited_states[idx])
      {
        if (placing)
          map[add_r][add_c] = original_char;
        return true;
      }
      visited_states[idx] = true;
    }
  }

  if (placing)
    map[add_r][add_c] = original_char;
  return false;
}

int32_t day06_part2(const std::vector<std::string> &input)
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

  std::vector<std::string> map = input;
  std::vector<bool> visited_states_global(rows * cols * 4, false);
  std::vector<bool> visited_positions(rows * cols, false);
  {
    int r = guard_r, c = guard_c, d = dir;
    visited_positions[r * cols + c] = true;
    visited_states_global[state_index(r, c, d, cols)] = true;
    while (true)
    {
      int nr = r + drow[d];
      int nc = c + dcol[d];
      bool blocked = false;
      if (nr < 0 || nr >= rows || nc < 0 || nc >= cols)
        break;
      if (map[nr][nc] == '#')
        blocked = true;

      if (blocked)
      {
        d = (d + 1) % 4;
        if (visited_states_global[state_index(r, c, d, cols)])
          break;
        visited_states_global[state_index(r, c, d, cols)] = true;
      }
      else
      {
        r = nr;
        c = nc;
        visited_positions[r * cols + c] = true;
        if (visited_states_global[state_index(r, c, d, cols)])
          break;
        visited_states_global[state_index(r, c, d, cols)] = true;
      }
    }
  }

  std::vector<bool> visited_states(rows * cols * 4, false);
  int32_t count = 0;
  for (int rr = 0; rr < rows; ++rr)
  {
    for (int cc = 0; cc < cols; ++cc)
    {
      if (rr == guard_r && cc == guard_c)
        continue;
      if (map[rr][cc] == '.' && visited_positions[rr * cols + cc])
      {
        bool loop = simulate_with_extra_obstacle(map, rr, cc,
                                                 guard_r, guard_c, dir,
                                                 visited_states, rows, cols);
        if (loop)
          count++;
      }
    }
  }

  return count;
}