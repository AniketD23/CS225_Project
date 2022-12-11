#include "bfs.h"

BFS::BFS(DataProcessor& data) { dp = data; }

void BFS::breadthFirst(std::string film) { breadthFirst(dp.titleToID(film)); }

void BFS::breadthFirst(int node) {
  std::unordered_map<int, std::unordered_map<int, double>>& adjacency = dp.avg_adj_list_;

  std::vector<bool> visited;
  visited.resize(adjacency.size(), false);

  std::queue<int> q;
  visited[node] = true;
  q.push(node);

  while (!q.empty()) {
    node = q.front();
    BFT.push_back(dp.IDToTitle(node));
    q.pop();

    for (auto neighbor : dp.getNeighbors(node)) {
      if (!visited[neighbor.first]) {
        visited[neighbor.first] = true;
        q.push(neighbor.first);
      }
    }
  }
}

std::vector<std::string> BFS::traversal() { return BFT; }
