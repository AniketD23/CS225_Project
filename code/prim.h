
#include <cfloat>
#include <climits>
#include <queue>

#include "data_processing.h"
#pragma once
/**
 * With the minimum spanning tree, we will print out the top 20 or so movies in
 * the tree closest to the root using a preorder traversal, and potentially
 * saving a larger number of movies to a file, formatted as a tree.
 */
class Prim {
 private:
  // representation of MST, boolean means
  // vertex is included in MST
  unordered_map<int, bool> mst_;
  // instance of data processor
  DataProcessor& dp_;
  // starting movie
  string start_;
  // id of starting movie
  int start_id_;
  // Vector to store order of nodes in Mst
  queue<int> parent_;
  // stores the value and weight of each node
  vector<int> list_;

 public:
  // default constructor
  // Prim() = default;
  /**
   *Constructor
   *@param string start
   *@param DataProcessor data
   */
  Prim(string start, DataProcessor& data);

  /**
   * find vertex with next most minimum weight
   * @param current current vertex
   */
  int nextMin();

  /**
   * execute algorithm
   * @return map<int, bool> of mst
   */
  queue<int> MST();
};
