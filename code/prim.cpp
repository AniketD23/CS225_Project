#include "prim.h"

Prim::Prim(string start, DataProcessor& data) : dp_(data) {
  start_ = start;
  // convert title
  int id = dp_.titleToID(start);
  start_id_ = id;
  // make starting element the root
  mst_.emplace(id, true);
  for (auto it : dp_.avg_adj_list_[start_id_]) {
    mst_.emplace(it.first, false);
  }
  parent_.push(start_id_);
}

int Prim::nextMin() {
  double min = DBL_MAX;
  int min_index = 0;
  for (auto it : mst_) {
    unordered_map<int, double> adj_nodes = dp_.getNeighbors(it.first);
    if (mst_[it.first] == false &&
        dp_.avg_adj_list_[it.first][parent_.front()] < min) {
      min = adj_nodes[parent_.front()];
      min_index = it.first;
    }
  }
  return min_index;
}

queue<int> Prim::MST() {
  for (size_t i = 0; i < mst_.size() - 1; i++) {
    int min = nextMin();
    mst_[min] = true;
    list_.push_back(min);
    unordered_map<int, double> neighbors = dp_.getNeighbors(min);
    for (auto neighbor : neighbors) {
      if (mst_.find(neighbor.first) != mst_.end()) {
        if (mst_[neighbor.first] == false &&
            neighbor.second <
                dp_.avg_adj_list_[parent_.front()][neighbor.first]) {
          parent_.push(neighbor.first);
        }
      }
    }
  }
  return parent_;
}
