#include "bfs.h"
#include <iostream>

BFS::BFS(DataProcessor& data) {
  dp = data;
}

void BFS::breadthFirst(std::string film1, std::string film2) {
  BFT.clear();
  breadthFirst(dp.titleToID(film1), dp.titleToID(film2));
}

void BFS::breadthFirst(int node1, int node2) {
  std::unordered_map<int, std::unordered_map<int, double>>& adjacency = dp.avg_adj_list_;

  std::vector<bool> visited;
  visited.resize(adjacency.size(), false);

  std::queue<int> q;
  visited[node1] = true;
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
      if (!visited[neighbor.first]) {
        visited[neighbor.first] = true; 
        q.push(neighbor.first);
      }
    }
  }
  
  
}

std::vector<std::string> BFS::traversal() {
  return BFT;
}