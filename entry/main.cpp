#include <fstream>
#include <iostream>
#include <sstream>

#include "data_processing.h"
#include "user_input.h"
#include "bfs.h"

int main(int argc, char** argv) {
  if (argc < 3) {
    std::cout << "Too few arguments. Remember, use \"algorithm name\" \"at least one movie argument...\"" << std::endl;
    return 0;
  }

  if (argv[1] == "A_star") {
    if (argc < 4) {
      std::cout << "Too few arguments for A_star. Remember, A_star takes two movie arguments" << std::endl;
      return 0;
    }
  } else if (argv[1] == "BFS") {
    if (argc < 4) {
      std::cout << "Too few arguments for BFS. Remember, BFS takes two movie arguments" << std::endl;
      return 0;
    }
  } else if (argv[1] == "Prim"){
    
  } else {
    std::cout << "Unknown algorithm. Remember, the first argument should be either \"A_star\", \"BFS\", or \"Prim\"." << std::endl;
    return 0;
  }

  DataProcessor d("../data/movies.dat", "../lists/avg_adj_list_.txt");
  return 0;
}
