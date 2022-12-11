/* #include "prim.h"

#include <climits>

Prim::Prim(string start, DataProcessor& data) : dp_(data) {
  start_ = start;
  // convert title
  int id = dp_.titleToID(start);
  // make starting element the root
  mst_.emplace(id, true);
}

int Prim::nextMin(int vertex) {
  map<int, int> adj_nodes = dp_.adj_list[vertex];
  int min = INT_MAX;
  for (size_t i = 0; i < adj_nodes.size(); i++) {
    int test = adj_nodes[vertex];
    if (dp_.adj_list[vertex][test] < min) {
      min = test;
    }
  }
  return min;
}

map<int, bool> Prim::MST(string start) {}
 */
