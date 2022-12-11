#include "data_processing.h"
#include <queue>

#pragma once

class BFS {
  public:
    BFS(DataProcessor& data);
    void breadthFirst(std::string film1, std::string film2);
    std::vector<std::string> traversal();
  
  private:
    DataProcessor dp;
    std::vector<std::string> BFT;   

    void breadthFirst(int node1, int node2);

};