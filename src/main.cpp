#include <iostream>
#include "solutions/day01.h"
#include "solutions/day02.h"
#include "solutions/day03.h"
#include "solutions/day04.h"
#include "solutions/day05.h"
#include "solutions/day06.h"
#include "solutions/day07.h"
#include "solutions/day08.h"
#include "solutions/day09.h"
#include "solutions/day10.h"
#include "solutions/day11.h"
#include "solutions/day12.h"
#include "solutions/utils/input_reader.h"
#include "solutions/utils/timer.h"

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
  case 6:
  {
    Timer t1("Day 06 Part 1");
    std::cout << "Day 06 Part 1: " << day06_part1(input) << "\n";
  }
    {
      Timer t2("Day 06 Part 2");
      std::cout << "Day 06 Part 2: " << day06_part2(input) << "\n";
    }
    break;
  case 7:
  {
    Timer t1("Day 07 Part 1");
    std::cout << "Day 07 Part 1: " << day07_part1(input) << "\n";
  }
    {
      Timer t2("Day 07 Part 2");
      std::cout << "Day 07 Part 2: " << day07_part2(input) << "\n";
    }
    break;
  case 8:
  {
    Timer t1("Day 08 Part 1");
    std::cout << "Day 08 Part 1: " << day08_part1(input) << "\n";
  }
    {
      Timer t2("Day 08 Part 2");
      std::cout << "Day 08 Part 2: " << day08_part2(input) << "\n";
    }
    break;
  case 9:
  {
    Timer t1("Day 09 Part 1");
    std::cout << "Day 09 Part 1: " << day09_part1(input) << "\n";
  }
    {
      Timer t2("Day 09 Part 2");
      std::cout << "Day 09 Part 2: " << day09_part2(input) << "\n";
    }
    break;
  case 10:
  {
    Timer t1("Day 10 Part 1");
    std::cout << "Day 10 Part 1: " << day10_part1(input) << "\n";
  }
    {
      Timer t2("Day 10 Part 2");
      std::cout << "Day 10 Part 2: " << day10_part2(input) << "\n";
    }
    break;
  case 11:
  {
    Timer t1("Day 11 Part 1");
    std::cout << "Day 11 Part 1: " << day11_part1(input) << "\n";
  }
    {
      Timer t2("Day 11 Part 2");
      std::cout << "Day 11 Part 2: " << day11_part2(input) << "\n";
    }
    break;
  case 12:
  {
    Timer t1("Day 12 Part 1");
    std::cout << "Day 12 Part 1: " << day12_part1(input) << "\n";
  }
    {
      Timer t2("Day 12 Part 2");
      std::cout << "Day 12 Part 2: " << day12_part2(input) << "\n";
    }
    break;
  default:
    std::cerr << "Day " << day << " not implemented\n";
    return 1;
  }
  return 0;
}