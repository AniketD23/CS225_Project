#include <fstream>
#include <iostream>
#include <sstream>

#include "data_processing.h"
#include "user_input.h"
#include "bfs.h"

int main(int argc, char** argv) {
  DataProcessor d("../data/movies.dat", "../lists/avg_adj_list_.txt");

  // UserInput ui(argv);
  // std::cout << ui.getTitle1() << std::endl;
  // std::cout << ui.getTitle2() << std::endl;
  return 0;
}
