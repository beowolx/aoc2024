#include <cstdint>
#include <vector>
#include <string>
#include <cassert>
#include <iostream>

int64_t day09_part1(const std::vector<std::string> &input)
{
  if (input.empty())
    return 0;
  const std::string &line = input[0];

  std::vector<int> file_lengths;
  std::vector<int> free_lengths;
  for (size_t i = 0; i < line.size(); ++i)
  {
    int length = line[i] - '0';
    if (i % 2 == 0)
    {
      file_lengths.push_back(length);
    }
    else
    {
      free_lengths.push_back(length);
    }
  }

  size_t fcount = file_lengths.size();
  size_t scount = free_lengths.size();

  std::vector<int> disk;
  disk.reserve(1000000);

  for (size_t i = 0; i < fcount; ++i)
  {
    int file_id = (int)i;
    int flen = file_lengths[i];
    for (int b = 0; b < flen; ++b)
    {
      disk.push_back(file_id);
    }

    if (i < scount)
    {
      int slen = free_lengths[i];
      for (int b = 0; b < slen; ++b)
      {
        disk.push_back(-1);
      }
    }
  }

  bool done = false;
  while (!done)
  {
    int lf = -1;
    for (int i = 0; i < (int)disk.size(); ++i)
    {
      if (disk[i] == -1)
      {
        lf = i;
        break;
      }
    }
    if (lf == -1)
    {
      done = true;
      break;
    }

    int rf = -1;
    for (int i = (int)disk.size() - 1; i >= 0; --i)
    {
      if (disk[i] != -1)
      {
        rf = i;
        break;
      }
    }

    if (rf < lf)
    {
      done = true;
      break;
    }

    disk[lf] = disk[rf];
    disk[rf] = -1;
  }

  int64_t checksum = 0;
  for (int64_t pos = 0; pos < (int64_t)disk.size(); ++pos)
  {
    int fid = disk[(size_t)pos];
    if (fid >= 0)
    {
      checksum += pos * fid;
    }
  }

  return (int64_t)checksum;
}

int32_t day09_part2(const std::vector<std::string> &input)
{
  return 0;
}