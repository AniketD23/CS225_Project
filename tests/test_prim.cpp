#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "prim.h"

void create_edge2(int a, int b, double weight, DataProcessor& data) {
  data.avg_adj_list_[a][b] = weight;
  data.avg_adj_list_[b][a] = weight;
}
void create_edge3(int a, int b,
                  std::unordered_map<int, std::unordered_map<int, bool>> arr) {
  arr[a][b] = true;
  arr[b][a] = true;
}

void check_tree(std::unordered_map<int, std::unordered_map<int, bool>> out,
                std::unordered_map<int, std::unordered_map<int, bool>> ans) {
  for (auto p : out) {
    std::cout << p.first << std::endl;
    for (auto p2 : p.second) {
      std::cout << p2.first << std::endl;
      std::cout << p2.second << std::endl;
      if (out[p.first].find(p2.first) != out[p.first].end()) {
        out[p.first][p2.first] = false;
      }
      REQUIRE(out[p.first][p2.first] == ans[p.first][p2.first]);
    }
  }
  for (auto p : ans) {
    for (auto p2 : p.second) {
      REQUIRE(out[p.first][p2.first] == ans[p.first][p2.first]);
    }
  }
}

TEST_CASE("prim test tree basic", "[primtree1]") {
  DataProcessor data;
  create_edge2(0, 1, 4.0, data);
  create_edge2(0, 7, 8.0, data);
  create_edge2(1, 7, 11.0, data);
  create_edge2(1, 2, 8.0, data);
  create_edge2(7, 8, 7.0, data);
  create_edge2(7, 6, 1.0, data);
  create_edge2(2, 8, 2.0, data);
  create_edge2(8, 6, 6.0, data);
  create_edge2(2, 5, 4.0, data);
  create_edge2(5, 3, 14.0, data);
  create_edge2(5, 4, 10.0, data);
  create_edge2(3, 4, 9.0, data);

  std::unordered_map<int, std::unordered_map<int, bool>> ans;

  create_edge3(0, 1, ans);
  create_edge3(1, 2, ans);
  create_edge3(2, 8, ans);
  create_edge3(2, 5, ans);
  create_edge3(5, 4, ans);
  create_edge3(3, 4, ans);
  create_edge3(8, 6, ans);
  create_edge3(6, 7, ans);

  std::unordered_map<int, std::unordered_map<int, bool>> out =
      Prim::findMST(data, "0");
  // for (auto p : out) {
  //   std::cout << "A" << std::endl;
  //   for (auto p2 : p.second) {
  //   std::cout << "B" << std::endl;
  //     std::cout << p.first << " to " << p2.first << std::endl;
  //     // REQUIRE(out[p.first][p2.first] == ans[p.first][p2.first]);
  //   }
  // }
  check_tree(out, ans);
}
TEST_CASE("Test 2 unconnected components", "[prim2]") {
  DataProcessor data;
  create_edge2(1, 2, 1, data);
  create_edge2(2, 3, 2, data);
  std::unordered_map<int, std::unordered_map<int, bool>> ans;
  create_edge3(1, 2, ans);
  create_edge3(2, 3, ans);
  std::unordered_map<int, std::unordered_map<int, bool>> out =
      Prim::findMST(data, "2");
  check_tree(out, ans);
}
TEST_CASE("Test 1 single node", "[prim2]") {
  DataProcessor data;
  create_edge2(1, 1, 1, data);
  std::unordered_map<int, std::unordered_map<int, bool>> ans;
  create_edge3(1, 1, ans);
  std::unordered_map<int, std::unordered_map<int, bool>> out =
      Prim::findMST(data, "1");
  check_tree(out, ans);
}

TEST_CASE("Test chain of nodes", "[prim3]") {
  DataProcessor data;
  create_edge2(1, 2, 1, data);
  create_edge2(2, 3, 2, data);
  create_edge2(3, 4, 3, data);
  std::unordered_map<int, std::unordered_map<int, bool>> ans;
  create_edge3(1, 2, ans);
  create_edge3(2, 3, ans);
  create_edge3(3, 4, ans);

  std::unordered_map<int, std::unordered_map<int, bool>> out =
      Prim::findMST(data, "1");
  check_tree(out, ans);
}

TEST_CASE("Test with avg_adj_list.txt", "[prim4]") {
  DataProcessor data("../data/movies.dat", "../lists/avg_adj_list_.txt");
  std::unordered_map<int, std::unordered_map<int, bool>> out =
      Prim::findMST(data, "The Room");

  std::vector<std::string> result =
      Prim::BFTraversalOfMST("The Room", 4, out, data);
  for (string movie : result) {
    std::cout << movie << std::endl;
  }
  REQUIRE(result.size() == 4);
  REQUIRE(result[0] == "The Room");
  REQUIRE(data.titleToID(result[1]) != -1);
  REQUIRE(data.titleToID(result[2]) != -1);
  REQUIRE(data.titleToID(result[3]) != -1);
}
