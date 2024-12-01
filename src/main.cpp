#include <iostream>
#include "solutions/day01.h"
#include "solutions/utils/input_reader.h"

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " <day_number>\n";
    return 1;
  }

  int day = std::stoi(argv[1]);
  auto input = read_input(day);

  switch (day)
  {
  case 1:
    std::cout << "Day 01 Part 1: " << day01_part1(input) << "\n";
    std::cout << "Day 01 Part 2: " << day01_part2(input) << "\n";
    break;
  default:
    std::cerr << "Day " << day << " not implemented\n";
    return 1;
  }
  return 0;
}