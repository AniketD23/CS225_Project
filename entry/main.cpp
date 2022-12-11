#include <fstream>
#include <iostream>
#include <sstream>

#include "data_processing.h"
#include "user_input.h"
#include "bfs.h"

int main(int argc, char** argv) {
  DataProcessor d("../data/movies.dat", "../lists/avg_adj_list_.txt");

  // DataProcessor proc;
  // proc.fileToListDouble("../lists/bfs_test.txt", proc.avg_adj_list_);

  std::cout << "initialize bfs" << std::endl;
  // BFS bfs(proc);
  BFS bfs(d);
  

  std::cout << "perform bfs" << std::endl;
  bfs.breadthFirst("The Avengers", "The Room");

  std::cout << "\nBFS of size: " << bfs.traversal().size() << std::endl;

  for (std::string e : bfs.traversal()) {
    std::cout << e << std::endl;
  }


  // UserInput ui(argv);
  // std::cout << ui.getTitle1() << std::endl;
  // std::cout << ui.getTitle2() << std::endl;
  return 0;
}
