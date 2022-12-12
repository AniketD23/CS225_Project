#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "a_star.h"

TEST_CASE("avd_adj_list test1", "[adj1]") {
  DataProcessor d("../data/movies.dat", "../lists/avg_adj_list_.txt");
  std::cout << "\nFinished processing nodes\n" << std::endl;
  double check = 1.0 * 5 / 3 + .1;
  double tol = .01;
  std::cout << d.avg_adj_list_[56][134] << std::endl;
  REQUIRE(((d.avg_adj_list_[56][134] < check + tol) &&
           (d.avg_adj_list_[56][134] > check - tol)));
}
