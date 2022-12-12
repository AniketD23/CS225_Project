#include "bfs.h"
#include <iostream>
#include <unordered_set>

BFS::BFS(DataProcessor& data) { dp = data; }

void BFS::breadthFirst(std::string film1, std::string film2) {
  if (dp.titleToID(film1) == 0 || dp.titleToID(film2) == 0) {
      std::cout << "That is not a valid film title! Please make sure your capitalization and punctuation is correct.\n";
      std::cout << "Note: Some films may not be included if they do not have enough common reviewers with any other films.\n";
      return;
  }
  BFT.clear();
  breadthFirst(dp.titleToID(film1), dp.titleToID(film2));
}

void BFS::breadthFirst(int node1, int node2) {
  std::unordered_map<int, std::unordered_map<int, double>>& adjacency = dp.avg_adj_list_;

  std::unordered_set<int> visited;

  std::queue<int> q;
  visited.insert(node1);
  q.push(node1);

  while (!q.empty()) {
    node1 = q.front();
    BFT.push_back(dp.IDToTitle(node1));
    q.pop();
    if (node1 == node2) {
      return;
    }

    for (auto neighbor : dp.getNeighbors(node1)) {
      // std::cout << "home: " << node1 << ", neighbor: " << neighbor.first << std::endl;
      if (visited.find(neighbor.first) == visited.end()) {
        visited.insert(neighbor.first);
        q.push(neighbor.first);
      }
    }
  }
}

std::vector<std::string> BFS::traversal() { return BFT; }
