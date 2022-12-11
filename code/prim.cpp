#include "prim.h"

Prim::Prim(string start, DataProcessor& data) : dp_(data) {
  start_ = start;
  // convert title
  int id = dp_.titleToID(start);
  start_id_ = id;
  // make starting element the root
  mst_.emplace(id, true);
  for (auto it : dp_.movie_id_dict_) {
    mst_.emplace(it.second.second, false);
  }
  parent_.push_back(start_id_);
}

int Prim::nextMin() {
  double min = DBL_MAX;
  int min_index = 0;
  for (auto it : mst_) {
    unordered_map<int, double> adj_nodes = dp_.getNeighbors(it.first);
    if (mst_[it.first] == false && adj_nodes[it.first] < min) {
      min = adj_nodes[it.first];
      min_index = it.first;
    }
  }
  return min_index;
}

vector<int> Prim::MST() {
  for (size_t i = 0; i < mst_.size() - 1; i++) {
    int min = nextMin();
    mst_[min] = true;
    unordered_map<int, double> neighbors = dp_.getNeighbors(min);
    for (auto neighbor : neighbors) {
      if (mst_[neighbor.first] == false && neighbor.second < neighbors[min]) {
        parent_.push_back(neighbor.first);
      }
    }
  }
  return parent_;
}
