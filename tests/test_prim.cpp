#include <prim.h>

#include <catch2/catch_test_macros.hpp>
#include <iostream>

void create_edge2(int a, int b, double weight, DataProcessor& data) {
  data.avg_adj_list_[a][b] = weight;
  data.avg_adj_list_[b][a] = weight;
}
void verify_path2(std::vector<std::pair<std::string, double>> a,
                  std::vector<std::string> b) {
  REQUIRE(a.size() == b.size());

  for (size_t i = 0; i < a.size(); i++) {
    REQUIRE(a[i].first == b[i]);
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
  queue<int> answer{{0, 1, 7, 6, 5, 2, 8, 3, 4}};

  Prim p("0", data);
  queue<int> user = p.MST();
  REQUIRE(answer == user);
}
