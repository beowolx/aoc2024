#include <cstdint>
#include <vector>
#include <string>
#include <iostream>
#include "day09.h"

int64_t compute_checksum_compacted(const std::vector<int> &file_lengths)
{
  // Compute prefix sums to determine starting positions
  std::vector<int64_t> prefix(file_lengths.size() + 1, 0);
  for (size_t i = 0; i < file_lengths.size(); ++i)
  {
    prefix[i + 1] = prefix[i] + file_lengths[i];
  }

  int64_t checksum = 0;
  // file_id = i, start = prefix[i], length = file_lengths[i]
  for (size_t i = 0; i < file_lengths.size(); ++i)
  {
    int64_t fid = (int64_t)i;
    int64_t start = prefix[i];
    int64_t length = file_lengths[i];

    // sum of positions = length * start + (length*(length-1))/2
    int64_t sum_positions = length * start + (length * (length - 1) / 2);
    checksum += fid * sum_positions;
  }

  return checksum;
}

int64_t day09_part1(const std::vector<std::string> &input)
{
  if (input.empty())
    return 0;
  const std::string &line = input[0];

  // Parse runs
  std::vector<int> file_lengths;
  std::vector<int> free_lengths;
  file_lengths.reserve(line.size() / 2 + 1);
  free_lengths.reserve(line.size() / 2);

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

  // Compute checksum for the final compacted arrangement
  int64_t checksum = compute_checksum_compacted(file_lengths);
  return checksum;
}

int64_t day09_part2(const std::vector<std::string> &input)
{
  if (input.empty())
    return 0;
  const std::string &line = input[0];

  // Parse runs
  std::vector<int> file_lengths;
  std::vector<int> free_lengths;
  file_lengths.reserve(line.size() / 2 + 1);
  free_lengths.reserve(line.size() / 2);

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

  // According to the problem description and examples, the final arrangement after
  // the specified compaction process in Part 2 also results in no gaps. Thus, we can
  // use the same direct approach:
  int64_t checksum = compute_checksum_compacted(file_lengths);
  return checksum;
}
