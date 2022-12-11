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
  static vector<pair<string, double>> shortestPath(string start, string end,
                                     DataProcessor& data);
  static double heuristic(int start_id, int end_id, DataProcessor& data);
  static vector<pair<string, double>> backtrack(int start, int end,
                                  std::unordered_map<int, int>& came_from,
                                  DataProcessor& data, std::unordered_map<int, double>& g_score);
};

class CompClass {
  public:
  bool operator() (pair<double, int> a, pair<double, int> b) {
    return a.first > b.first;
  }
};
