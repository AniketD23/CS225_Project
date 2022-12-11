#include <iostream>
#include <ostream>

#include "data_processing.h"
#pragma once
using namespace std;
class UserInput {
  public:
  static void runBFS(DataProcessor& d, std::string start, std::string end, std::string output_filename);
  static void runBFS(DataProcessor& d, std::string start, std::string end);

  static void runA_star(DataProcessor& d, std::string start, std::string end, std::string output_filename);
  static void runA_star(DataProcessor& d, std::string start, std::string end);
};
