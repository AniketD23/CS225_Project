#include <functional>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <unordered_map>

#include "data_processing.h"

using namespace std;
class A_Star {
  public:
  static vector<string> shortestPath(string start, string end,
                                     DataProcessor& data);
  static int heuristic(int start_id, int end_id, DataProcessor& data);
  static vector<string> backtrack(int start, int end,
                                  std::unordered_map<int, int>& came_from,
                                  DataProcessor& data);
};

class CompClass {
  public:
  bool operator() (pair<double, int> a, pair<double, int> b) {
    return a.first > b.first;
  }
};
