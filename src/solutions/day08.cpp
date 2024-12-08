#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <utility>
#include <functional>

struct Coord
{
  int x;
  int y;
};

struct CoordHash
{
  std::size_t operator()(const Coord &c) const
  {
    return std::hash<int>()(c.x) ^ (std::hash<int>()(c.y) << 1);
  }
};

struct CoordEq
{
  bool operator()(const Coord &a, const Coord &b) const
  {
    return a.x == b.x && a.y == b.y;
  }
};

int32_t day08_part1(const std::vector<std::string> &input)
{
  int height = (int)input.size();
  if (height == 0)
    return 0;
  int width = (int)input[0].size();

  std::unordered_map<char, std::vector<Coord>> freq_map;
  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      char c = input[y][x];
      if (c != '.')
      {
        freq_map[c].push_back({x, y});
      }
    }
  }

  std::unordered_set<Coord, CoordHash, CoordEq> antinodes;

  for (auto &kv : freq_map)
  {
    const auto &positions = kv.second;
    for (size_t i = 0; i < positions.size(); ++i)
    {
      for (size_t j = i + 1; j < positions.size(); ++j)
      {
        const Coord &A = positions[i];
        const Coord &B = positions[j];

        Coord C1 = {2 * A.x - B.x, 2 * A.y - B.y};
        if (C1.x >= 0 && C1.x < width && C1.y >= 0 && C1.y < height)
        {
          antinodes.insert(C1);
        }

        Coord C2 = {2 * B.x - A.x, 2 * B.y - A.y};
        if (C2.x >= 0 && C2.x < width && C2.y >= 0 && C2.y < height)
        {
          antinodes.insert(C2);
        }
      }
    }
  }

  return (int32_t)antinodes.size();
}

int32_t day08_part2(const std::vector<std::string> &input)
{
  return 0;
}