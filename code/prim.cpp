#include "prim.h"

std::unordered_map<int, std::unordered_map<int, bool>> Prim::findMST(
    DataProcessor& d, std::string start) {
  std::priority_queue<std::pair<int, double>, vector<std::pair<int, double>>,
                      PrimCompClass>
      to_add;
  std::unordered_map<int, double> least_known;
  std::unordered_set<int> in_tree;
  std::unordered_set<int> to_check;
  std::unordered_map<int, int> parent;
  std::unordered_map<int, std::unordered_map<int, bool>> mst;

  int start_id = d.titleToID(start);
  to_add.push(std::make_pair(start_id, 0.0));
  to_check.insert(start_id);

  while (!to_add.empty()) {
    while (to_check.count(to_add.top().first) == 0) {
      to_add.pop();
      if (to_add.empty()) {
        return mst;
      }
    }
    int curr_id = to_add.top().first;
    to_add.pop();
    to_check.erase(curr_id);
    in_tree.insert(curr_id);
    mst[curr_id][parent[curr_id]] = true;
    mst[parent[curr_id]][curr_id] = true;
    for (auto p : d.getNeighbors(curr_id)) {
      if ((in_tree.count(p.first) == 0) && (least_known.count(p.first) == 0 ||
                                            p.second < least_known[p.first])) {
        least_known[p.first] = p.second;
        to_add.push(p);
        to_check.insert(p.first);
        parent[p.first] = curr_id;
      }
    }
  }
  return mst;
}

std::vector<std::string> BFTraversalOfMST(std::string root, int num_nodes, std::unordered_map<int, std::unordered_map<int, bool>>& mst, DataProcessor& data) {
  int root_id = data.titleToID(root);
  std::queue<int> to_add;
  to_add.push(root_id);
  std::unordered_set<int> visited;

  std::vector<std::string> out;
  while (!to_add.empty() && (num_nodes > 0 || num_nodes <= -1)) {
    int curr_id = to_add.front();
    out.push_back(data.IDToTitle(curr_id));
    num_nodes--;
    to_add.pop();
    visited.insert(curr_id);

    for (auto p : mst[to_add.front()]) {
      if (p.second && visited.count(p.first) == 0) {
        to_add.push(p.first);
      }
    }
  }
  return out;
}

