#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "a_star.h"

TEST_CASE("avd_adj_list test1", "[adj1]") {
  DataProcessor d;
  REQUIRE(d.avg_adj_list_[56][134] == (5 / 3));
}
