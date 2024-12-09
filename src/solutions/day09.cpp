#include <cstdint>
#include <vector>
#include <string>
#include "day09.h"
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

int64_t day09_part2(const std::vector<std::string> &input)
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
  {
    int file_id = 0;
    for (size_t i = 0; i < fcount; ++i)
    {
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
      file_id++;
    }
  }

  struct FileInfo
  {
    int start = -1;
    int length = 0;
  };

  std::vector<FileInfo> files(fcount);
  for (int i = 0; i < (int)disk.size(); ++i)
  {
    int fid = disk[i];
    if (fid >= 0)
    {
      if (files[(size_t)fid].start == -1)
        files[(size_t)fid].start = i;
      files[(size_t)fid].length++;
    }
  }

  auto find_suitable_segment = [&](int file_start, int file_length) -> int
  {
    int needed = file_length;
    int count = 0;
    int segment_start = -1;
    int best_start = -1;

    for (int i = 0; i < file_start; ++i)
    {
      if (disk[i] == -1)
      {
        if (count == 0)
          segment_start = i;
        count++;
        if (count >= needed)
        {
          best_start = segment_start;
          break;
        }
      }
      else
      {
        count = 0;
        segment_start = -1;
      }
    }

    return best_start;
  };

  for (int fid = (int)fcount - 1; fid >= 0; --fid)
  {
    if (files[(size_t)fid].length == 0)
    {
      continue;
    }

    int start = files[(size_t)fid].start;
    int length = files[(size_t)fid].length;

    int new_start = find_suitable_segment(start, length);
    if (new_start == -1)
    {
      continue;
    }

    int file_end = start + length - 1;

    std::vector<int> file_blocks;
    file_blocks.reserve((size_t)length);
    for (int pos = start; pos <= file_end; ++pos)
    {
      file_blocks.push_back(disk[pos]);
      disk[pos] = -1;
    }

    for (int i = 0; i < length; ++i)
    {
      disk[new_start + i] = file_blocks[i];
    }

    files[(size_t)fid].start = new_start;
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