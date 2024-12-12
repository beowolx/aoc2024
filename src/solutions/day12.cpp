#include "day12.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <unordered_set>

std::tuple<int, int> calculate_region_properties(const std::vector<std::string> &grid, int row, int col, char plant_type, std::vector<std::vector<bool>> &visited)
{
  int area = 0;
  int perimeter = 0;
  int rows = grid.size();
  int cols = grid[0].size();

  std::vector<std::pair<int, int>> stack;
  stack.push_back({row, col});
  visited[row][col] = true;

  while (!stack.empty())
  {
    int r = stack.back().first;
    int c = stack.back().second;
    stack.pop_back();

    area++;
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    for (int i = 0; i < 4; ++i)
    {
      int nr = r + dr[i];
      int nc = c + dc[i];

      if (nr >= 0 && nr < rows && nc >= 0 && nc < cols)
      {
        if (grid[nr][nc] == plant_type)
        {
          if (!visited[nr][nc])
          {
            stack.push_back({nr, nc});
            visited[nr][nc] = true;
          }
        }
        else
        {
          perimeter++;
        }
      }
      else
      {
        perimeter++;
      }
    }
  }
  return std::make_tuple(area, perimeter);
}

int32_t day12_part1(const std::vector<std::string> &input)
{

  int32_t total_price = 0;
  int rows = input.size();
  if (rows == 0)
    return 0;
  int cols = input[0].size();
  if (cols == 0)
    return 0;

  std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

  for (int r = 0; r < rows; ++r)
  {
    for (int c = 0; c < cols; ++c)
    {
      if (!visited[r][c])
      {
        char plant_type = input[r][c];
        int area, perimeter;
        std::tie(area, perimeter) = calculate_region_properties(input, r, c, plant_type, visited);
        total_price += area * perimeter;
      }
    }
  }
  return total_price;
}

struct Point
{
  int r, c;
  Point(int row, int col) : r(row), c(col) {}

  bool operator==(const Point &other) const
  {
    return r == other.r && c == other.c;
  }
};

struct PointHash
{
  std::size_t operator()(const Point &p) const
  {
    return std::hash<int>()(p.r) ^ (std::hash<int>()(p.c) << 1);
  }
};

std::tuple<int, int> calculate_region_sides(const std::vector<std::string> &grid, int row, int col,
                                            char plant_type, std::vector<std::vector<bool>> &visited)
{
  int area = 0;
  std::unordered_set<Point, PointHash> region_points;
  int rows = grid.size();
  int cols = grid[0].size();

  std::vector<std::pair<int, int>> stack;
  stack.push_back({row, col});
  visited[row][col] = true;

  while (!stack.empty())
  {
    auto [r, c] = stack.back();
    stack.pop_back();

    area++;
    region_points.insert(Point(r, c));

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    for (int i = 0; i < 4; ++i)
    {
      int nr = r + dr[i];
      int nc = c + dc[i];

      if (nr >= 0 && nr < rows && nc >= 0 && nc < cols &&
          !visited[nr][nc] && grid[nr][nc] == plant_type)
      {
        stack.push_back({nr, nc});
        visited[nr][nc] = true;
      }
    }
  }

  int sides = 0;
  std::unordered_set<std::string> unique_sides;

  for (const auto &point : region_points)
  {
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    for (int i = 0; i < 4; ++i)
    {
      int nr = point.r + dr[i];
      int nc = point.c + dc[i];

      if (nr < 0 || nr >= rows || nc < 0 || nc >= cols ||
          grid[nr][nc] != plant_type)
      {
        std::string side_id;
        if (i < 2)
        {
          int min_r = std::min(point.r, nr);
          side_id = "v_" + std::to_string(min_r) + "_" + std::to_string(point.c);
        }
        else
        {
          int min_c = std::min(point.c, nc);
          side_id = "h_" + std::to_string(point.r) + "_" + std::to_string(min_c);
        }
        unique_sides.insert(side_id);
      }
    }
  }

  return std::make_tuple(area, unique_sides.size());
}

std::vector<std::pair<int, int>> collect_region(const std::vector<std::string> &grid, int row, int col, char plant_type, std::vector<std::vector<bool>> &visited)
{
  int rows = (int)grid.size();
  int cols = (int)grid[0].size();

  std::vector<std::pair<int, int>> region_cells;
  std::vector<std::pair<int, int>> stack;
  stack.push_back({row, col});
  visited[row][col] = true;

  while (!stack.empty())
  {
    auto [r, c] = stack.back();
    stack.pop_back();
    region_cells.push_back({r, c});

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    for (int i = 0; i < 4; ++i)
    {
      int nr = r + dr[i];
      int nc = c + dc[i];
      if (nr >= 0 && nr < rows && nc >= 0 && nc < cols)
      {
        if (!visited[nr][nc] && grid[nr][nc] == plant_type)
        {
          visited[nr][nc] = true;
          stack.push_back({nr, nc});
        }
      }
    }
  }
  return region_cells;
}

int count_sides(const std::vector<std::string> &grid, const std::vector<std::pair<int, int>> &region_cells)
{
  if (region_cells.empty())
    return 0;

  int min_r = region_cells[0].first;
  int max_r = region_cells[0].first;
  int min_c = region_cells[0].second;
  int max_c = region_cells[0].second;

  for (auto &cell : region_cells)
  {
    min_r = std::min(min_r, cell.first);
    max_r = std::max(max_r, cell.first);
    min_c = std::min(min_c, cell.second);
    max_c = std::max(max_c, cell.second);
  }

  int region_height = max_r - min_r + 1;
  int region_width = max_c - min_c + 1;

  std::vector<std::vector<bool>> in_region(region_height, std::vector<bool>(region_width, false));
  for (auto &cell : region_cells)
  {
    in_region[cell.first - min_r][cell.second - min_c] = true;
  }

  int sides = 0;

  for (int r = 0; r < region_height; ++r)
  {
    bool in_top_run = false;
    for (int c = 0; c < region_width; ++c)
    {
      bool top_edge = in_region[r][c] && ((r == 0) || !in_region[r - 1][c]);
      if (top_edge && !in_top_run)
      {
        sides++;
        in_top_run = true;
      }
      else if (!top_edge)
      {
        in_top_run = false;
      }
    }

    bool in_bottom_run = false;
    for (int c = 0; c < region_width; ++c)
    {
      bool bottom_edge = in_region[r][c] && ((r == region_height - 1) || !in_region[r + 1][c]);
      if (bottom_edge && !in_bottom_run)
      {
        sides++;
        in_bottom_run = true;
      }
      else if (!bottom_edge)
      {
        in_bottom_run = false;
      }
    }
  }

  for (int c = 0; c < region_width; ++c)
  {
    bool in_left_run = false;
    for (int r = 0; r < region_height; ++r)
    {
      bool left_edge = in_region[r][c] && ((c == 0) || !in_region[r][c - 1]);
      if (left_edge && !in_left_run)
      {
        sides++;
        in_left_run = true;
      }
      else if (!left_edge)
      {
        in_left_run = false;
      }
    }

    bool in_right_run = false;
    for (int r = 0; r < region_height; ++r)
    {
      bool right_edge = in_region[r][c] && ((c == region_width - 1) || !in_region[r][c + 1]);
      if (right_edge && !in_right_run)
      {
        sides++;
        in_right_run = true;
      }
      else if (!right_edge)
      {
        in_right_run = false;
      }
    }
  }

  return sides;
}

int32_t day12_part2(const std::vector<std::string> &input)
{
  int rows = input.size();
  if (rows == 0)
    return 0;
  int cols = input[0].size();
  if (cols == 0)
    return 0;

  std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
  int32_t total_price = 0;

  for (int r = 0; r < rows; ++r)
  {
    for (int c = 0; c < cols; ++c)
    {
      if (!visited[r][c])
      {
        char plant_type = input[r][c];
        auto region = collect_region(input, r, c, plant_type, visited);

        int area = region.size();
        int sides = count_sides(input, region);
        total_price += area * sides;
      }
    }
  }

  return total_price;
}
