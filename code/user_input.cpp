#include "user_input.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <sstream>
#include "prim.h"
#include "a_star.h"
#include "bfs.h"
#include <iomanip>

void UserInput::runBFS(DataProcessor& d, std::string start, std::string end, std::string output_filename) {
  output_filename = "../out/" + output_filename;
  std::cout << "\nInitialize bfs" << std::endl;
  BFS bfs(d);
  
  std::cout << "Perform bfs" << std::endl;
  bfs.breadthFirst(start, end);

  std::cout << "\nBFS of size: " << bfs.traversal().size() << std::endl;
  std::ofstream os;
  os.open(output_filename, std::ofstream::out | std::ofstream::trunc);
  // os.open("../out/BFS_out.txt", std::ofstream::out | std::ofstream::trunc);

  for (std::string e : bfs.traversal()) {
    os << e << '\n';
  }
  std::cout << "BFS written to file at " << output_filename << std::endl;
}
void UserInput::runBFS(DataProcessor& d, std::string start, std::string end) {
  runBFS(d, start, end, "BFS_out.txt");
}

void UserInput::runA_star(DataProcessor& d, std::string start, std::string end, std::string output_filename) {
  output_filename = "../out/" + output_filename;
  
  std::cout << "\nRunning A_star" << std::endl;
  auto out = A_Star::shortestPath(start, end, d);

  int table_width = 50;
  std::cout << "Movie Title" << std::setw(table_width - 11) << "\"Distance\"" << std::endl;

  for (auto p : out) {
    if (p.first.size() > 40) {
      p.first = p.first.substr(0, 40) + "...";
    }
    std::cout << p.first << std::setw(table_width - p.first.size()) << p.second << std::endl;
  }

  std::ofstream os;
  os.open(output_filename, std::ofstream::out | std::ofstream::trunc);
  os << "Movie Title" << std::setw(table_width - 11) << "\"Distance\"" << "\n";
  for (auto p : out) {
    if (p.first.size() > 40) {
      p.first = p.first.substr(0, 40) + "...";
    }
    os << p.first << std::setw(table_width - p.first.size()) << p.second << "\n";
  }
  std::cout << "A_star written to file at " << output_filename << std::endl;
}

void UserInput::runA_star(DataProcessor& d, std::string start, std::string end) {
  runA_star(d, start, end, "A_star_out.txt");
}
