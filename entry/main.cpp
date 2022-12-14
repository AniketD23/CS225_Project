#include <string.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include "data_processing.h"
#include "user_input.h"

int main(int argc, char** argv) {
  if (argc < 3) {
    std::cout << "Too few arguments. Remember, use [\"algorithm name\" \"movie "
                 "1\" \"movie 2\" \"output file name\"]"
              << std::endl;
    return 0;
  }
  std::string movie_id_file = "../data/movies.dat";
  std::string adj_list_file = "../lists/avg_adj_list_.txt";
  if (!strcmp(argv[1], "A_star")) {
    if (argc < 4) {
      std::cout << "Too few arguments for A_star. Remember, A_star takes two "
                   "movie arguments."
                << std::endl;
      return 0;
    }
    DataProcessor d(movie_id_file, adj_list_file);
    if (d.titleToID(argv[2]) == -1 || d.titleToID(argv[3]) == -1) {
      std::cout << "One of the movies passed is not in the dataset. Remember "
                   "to be strict with capitalization."
                << std::endl;
      return 0;
    }
    if (argc < 5) {
      UserInput::runA_star(d, argv[2], argv[3]);
    } else {
      UserInput::runA_star(d, argv[2], argv[3], argv[4]);
    }
    return 0;

  } else if (!strcmp(argv[1], "BFS")) {
    if (argc < 4) {
      std::cout << "Too few arguments for BFS. Remember, BFS takes two movie "
                   "arguments."
                << std::endl;
      return 0;
    }
    DataProcessor d(movie_id_file, adj_list_file);
    if (d.titleToID(argv[2]) == -1 || d.titleToID(argv[3]) == -1) {
      std::cout << "One of the movies passed is not in the dataset. Remember "
                   "to be strict with capitalization."
                << std::endl;
      return 0;
    }
    if (argc < 5) {
      UserInput::runBFS(d, argv[2], argv[3]);
    } else {
      UserInput::runBFS(d, argv[2], argv[3], argv[4]);
    }
    return 0;
  } else if (!strcmp(argv[1], "Prim")) {
    DataProcessor d(movie_id_file, adj_list_file);
    if (d.titleToID(argv[2]) == -1) {
      std::cout << "One of the movies passed is not in the dataset. Remember "
                   "to be strict with capitalization."
                << std::endl;
      return 0;
    }
    if (argc < 4) {
      UserInput::runPrim(d, argv[2]);
    } else {
      UserInput::runPrim(d, argv[2], argv[3]);
    }
  } else {
    std::cout << "Unknown algorithm. Remember, the first argument should be "
                 "either \"A_star\", \"BFS\", or \"Prim\"."
              << std::endl;
    return 0;
  }
}
