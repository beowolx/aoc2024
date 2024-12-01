#include "input_reader.h"
#include <fstream>
#include <sstream>
#include <iomanip>

std::vector<std::string> read_input(int day)
{
  std::stringstream ss;
  ss << "input/day" << std::setfill('0') << std::setw(2) << day << ".txt";

  std::ifstream file(ss.str());
  std::vector<std::string> lines;
  std::string line;

  while (std::getline(file, line))
  {
    lines.push_back(line);
  }

  return lines;
}