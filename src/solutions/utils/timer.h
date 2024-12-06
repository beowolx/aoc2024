#pragma once
#include <chrono>
#include <string>

class Timer
{
private:
  std::chrono::high_resolution_clock::time_point start_time;
  std::string name;

public:
  Timer(const std::string &name = "") : name(name)
  {
    start_time = std::chrono::high_resolution_clock::now();
  }

  ~Timer()
  {
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    printf("%s took %lld microseconds\n", name.empty() ? "Operation" : name.c_str(), duration.count());
  }
};