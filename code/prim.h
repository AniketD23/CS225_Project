
#include <cfloat>
#include <climits>
#include <queue>
#include <unordered_map>
#include <unordered_set>

#include "data_processing.h"
#pragma once
/**
 * With the minimum spanning tree, we will print out the top 20 or so movies in
 * the tree closest to the root using a preorder traversal, and potentially
 * saving a larger number of movies to a file, formatted as a tree.
 */
class Prim {
 public:
  static std::unordered_map<int, std::unordered_map<int, bool>> findMST(
      DataProcessor& d, std::string start);
};

class PrimCompClass {
 public:
  bool operator()(pair<int, double> a, pair<int, double> b) {
    if (a.second == b.second) {
      return a.first > b.first;
    }
    return a.second > b.second;
  }
};
