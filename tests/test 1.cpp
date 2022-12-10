#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "/workspaces/cs225/CS225_Project/code/a_star.h"
#include "/workspaces/cs225/CS225_Project/code/data_processing.h"
#include "/workspaces/cs225/CS225_Project/code/prim.h"

TEST_CASE("avd_adj_list test1", "[adj1]") {
  DataProcessor d;
  REQUIRE(d.avg_adj_list_[56][134] == (5 / 3));
}
