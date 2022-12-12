#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "bfs.h"
#include "unordered_set"

TEST_CASE("full BFS", "[bfs]") {
  DataProcessor proc;
  proc.fileToListDouble("../lists/bfs_test.txt", proc.avg_adj_list_);
  BFS bfs(proc);

  bfs.breadthFirst("0", "6");
  std::vector<std::string> out = bfs.traversal();

  // std::cout << "\nfirst bfs:" << std::endl;
  // for (std::string e : out) {
  //   std::cout << e << std::endl;
  // }
  // std::cout << "A" << std::endl;
  
  std::unordered_set<std::string> dist_1 = {"1", "2"};
  std::unordered_set<std::string> dist_2 = {"3", "4", "5"};
  std::unordered_set<std::string> dist_3 = {"6"};

  REQUIRE(out.front() == "0");
  for (unsigned i = 1; i < out.size(); i++) {
    if (i < 3) {
      REQUIRE(dist_1.find(out[i]) != dist_1.end());
    } else if (i < 6) {
      REQUIRE(dist_2.find(out[i]) != dist_2.end());
    } else {
      REQUIRE(dist_3.find(out[i]) != dist_3.end());
    }
  }

  bfs.breadthFirst("6", "0");
  out = bfs.traversal();

  // std::cout << "second bfs:" << std::endl;
  // for (std::string e : out) {
  //   std::cout << e << std::endl;
  // }

  dist_1 = {"4"};
  dist_2 = {"2", "3"};
  dist_3 = {"0", "1", "5"};

  REQUIRE(out.front() == "6");
  for (unsigned i = 1; i < out.size(); i++) {
    if (i < 2) {
      REQUIRE(dist_1.find(out[i]) != dist_1.end());
    } else if (i < 4) {
      REQUIRE(dist_2.find(out[i]) != dist_2.end());
    } else {
      REQUIRE(dist_3.find(out[i]) != dist_3.end());
    }
  }

  bfs.breadthFirst("5", "6");
  out = bfs.traversal();

  // std::cout << "third bfs:" << std::endl;
  // for (std::string e : out) {
  //   std::cout << e << std::endl;
  // }

  dist_1 = {"1", "3"};
  dist_2 = {"0", "2", "4"};
  dist_3 = {"6"};

  REQUIRE(out.front() == "5");
  for (unsigned i = 1; i < out.size(); i++) {
    if (i < 3) {
      REQUIRE(dist_1.find(out[i]) != dist_1.end());
    } else if (i < 6) {
      REQUIRE(dist_2.find(out[i]) != dist_2.end());
    } else {
      REQUIRE(dist_3.find(out[i]) != dist_3.end());
    }
  }
}

TEST_CASE("partial BFS", "[bfs]") {
  DataProcessor proc;
  proc.fileToListDouble("../lists/bfs_test.txt", proc.avg_adj_list_);
  BFS bfs(proc);

  bfs.breadthFirst("0", "4");
  std::vector<std::string> out = bfs.traversal();

  std::unordered_set<std::string> dist_1 = {"1", "2"};
  std::unordered_set<std::string> dist_2 = {"3", "4", "5"};
  std::unordered_set<std::string> dist_3;

  REQUIRE(out.front() == "0");
  for (unsigned i = 1; i < out.size(); i++) {
    if (i < 3) {
      REQUIRE(dist_1.find(out[i]) != dist_1.end());
    } else {
      REQUIRE(dist_2.find(out[i]) != dist_2.end());
    }
  }

  bfs.breadthFirst("6", "5");
  out = bfs.traversal();

  dist_1 = {"4"};
  dist_2 = {"2", "3"};
  dist_3 = {"0", "1", "5"};

  REQUIRE(out.front() == "6");
  for (unsigned i = 1; i < out.size(); i++) {
    if (i < 2) {
      REQUIRE(dist_1.find(out[i]) != dist_1.end());
    } else if (i < 4) {
      REQUIRE(dist_2.find(out[i]) != dist_2.end());
    } else {
      REQUIRE(dist_3.find(out[i]) != dist_3.end());
    }
  }

  bfs.breadthFirst("5", "2");
  out = bfs.traversal();

  dist_1 = {"1", "3"};
  dist_2 = {"0", "2", "4"};

  REQUIRE(out.front() == "5");
  for (unsigned i = 1; i < out.size(); i++) {
    if (i < 3) {
      REQUIRE(dist_1.find(out[i]) != dist_1.end());
    } else {
      REQUIRE(dist_2.find(out[i]) != dist_2.end());
    }
  }
}
