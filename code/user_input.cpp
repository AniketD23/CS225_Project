#include "user_input.h"

#include <chrono>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <ostream>
#include <sstream>

#include "a_star.h"
#include "bfs.h"
#include "prim.h"

void UserInput::runBFS(DataProcessor& d, std::string start, std::string end,
                       std::string output_filename) {
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

void UserInput::runA_star(DataProcessor& d, std::string start, std::string end,
                          std::string output_filename) {
  output_filename = "../out/" + output_filename;

  std::cout << "Running A_star\n" << std::endl;
  auto out = A_Star::shortestPath(start, end, d);

  int table_width = 60;
  std::cout << "Movie Title" << std::setw(table_width - 11)
            << "\"Distance\" from start" << std::endl;

  for (auto p : out) {
    if (p.first.size() > 40) {
      p.first = p.first.substr(0, 40) + "...";
    }
    std::cout << p.first << std::setw(table_width - p.first.size()) << p.second
              << std::endl;
  }

  std::ofstream os;
  os.open(output_filename, std::ofstream::out | std::ofstream::trunc);
  os << "Movie Title" << std::setw(table_width - 11) << "\"Distance\""
     << "\n";
  for (auto p : out) {
    if (p.first.size() > 40) {
      p.first = p.first.substr(0, 40) + "...";
    }
    os << p.first << std::setw(table_width - p.first.size()) << p.second
       << "\n";
  }
  std::cout << "A_star written to file at " << output_filename << std::endl;
}

void UserInput::runA_star(DataProcessor& d, std::string start,
                          std::string end) {
  std::chrono::steady_clock::time_point begin =
      std::chrono::steady_clock::now();
  // cout << "F runtime=" << measure<>::duration(runA_star(d, start, end,
  // "A_star_out.txt")).count() << "ms";
  runA_star(d, start, end, "A_star_out.txt");
  std::chrono::steady_clock::time_point done = std::chrono::steady_clock::now();
  std::cout << "\nA_star running time (sec) = "
            << (std::chrono::duration_cast<std::chrono::microseconds>(done -
                                                                      begin)
                    .count()) /
                   1000000.0
            << std::endl;
}

void UserInput::runPrim(DataProcessor& d, std::string start,
                        std::string output_filename) {
  output_filename = "../out/" + output_filename;
  std::cout << "Running Prim (estimated load time: 1-3 minutes) \n"
            << std::endl;
  auto result_map = Prim::findMST(d, start);
  std::cout << "How many movie reccomendations would you like to see?\n"
            << std::endl;
  size_t num_movies = result_map.size();
  std::cout << "Enter a number from 3 - " << num_movies << '\n' << std::endl;
  int nodes;
  std::cin >> nodes;
  if (nodes < 3 || nodes > int(num_movies)) {
    std::cout << "Please enter a valid number from 3 -" << num_movies << '\n'
              << std::endl;
    return;
  }
  auto out = Prim::BFTraversalOfMST(start, nodes, result_map, d);
  std::ofstream os;
  os.open(output_filename, std::ofstream::out | std::ofstream::trunc);
  for (string movie : out) {
    os << movie << '\n';
  }
  std::cout << "Prim's written to file at " << output_filename << std::endl;
}

void UserInput::runPrim(DataProcessor& d, std::string start) {
  runPrim(d, start, "Prim_out.txt");
}
