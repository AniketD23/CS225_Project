#include <fstream>
#include <iostream>
#include <sstream>

#include "data_processing.h"
#include "user_input.h"
#include "bfs.h"

int main(int argc, char** argv) {
  // DataProcessor d("../data/movies.dat", "../lists/avg_adj_list_.txt");

  DataProcessor proc;
  proc.fileToListDouble("../lists/bfs_test.txt", proc.avg_adj_list_);

  std::cout << "initialize bfs" << std::endl;
  BFS bfs(proc);

  std::cout << "perform bfs 1" << std::endl;
  bfs.breadthFirst("0", "6");

  std::cout << "\nBFS of size: " << bfs.traversal().size() << std::endl;

  for (std::string e : bfs.traversal()) {
    std::cout << e << std::endl;
  }

  // std::cout << "perform bfs 2" << std::endl;
  // bfs.breadthFirst("6", "0");

  // std::cout << "\nBFS of size: " << bfs.traversal().size() << std::endl;

  // for (std::string e : bfs.traversal()) {
  //   std::cout << e << std::endl;
  // }

  // std::cout << "perform bfs 3" << std::endl;
  // bfs.breadthFirst("5", "6");

  // std::cout << "\nBFS of size: " << bfs.traversal().size() << std::endl;

  // for (std::string e : bfs.traversal()) {
  //   std::cout << e << std::endl;
  // }

  // UserInput ui(argv);
  // std::cout << ui.getTitle1() << std::endl;
  // std::cout << ui.getTitle2() << std::endl;
  return 0;
}
