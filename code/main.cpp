#include <fstream>
#include <iostream>

#include "data_processing.h"

int main() {
  std::cout << "Start processing" << std::endl;
  DataProcessor d("../data/movies.dat", "../data/ratings.dat");
  std::cout << "\nFinish processing\n" << std::endl;

  //     std::cout << "Start writing" << std::endl;
  //     d.listToFile("../lists/num_weights_list.txt", d.num_weights_list);
  //     std::cout << "\nFinish writing\n" << std::endl;

  return 0;
}
