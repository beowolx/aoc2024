#include <iostream>
#include "solutions/day01.h"
#include "solutions/day02.h"
#include "solutions/day03.h"
#include "solutions/day04.h"
#include "solutions/day05.h"
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
  case 2:
    std::cout << "Day 02 Part 1: " << day02_part1(input) << "\n";
    std::cout << "Day 02 Part 2: " << day02_part2(input) << "\n";
    break;
  case 3:
    std::cout << "Day 03 Part 1: " << day03_part1(input) << "\n";
    std::cout << "Day 03 Part 2: " << day03_part2(input) << "\n";
    break;
  case 4:
    std::cout << "Day 04 Part 1: " << day04_part1(input) << "\n";
    std::cout << "Day 04 Part 2: " << day04_part2(input) << "\n";
    break;
  case 5:
    std::cout << "Day 05 Part 1: " << day05_part1(input) << "\n";
    std::cout << "Day 05 Part 2: " << day05_part2(input) << "\n";
    break;
  default:
    std::cerr << "Day " << day << " not implemented\n";
    return 1;
  }
  return 0;
}