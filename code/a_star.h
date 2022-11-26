#include "data_processing.h"
#include <string>
#include <vector>
#include <queue>
#include <set>

using namespace std;
class A_Star {
    static vector<string> shortestPath(string start, string end, DataProcessor& data);
    static int heuristic(int start_id, int end_id, DataProcessor& data);
    static vector<string> backtrack(int start, int end, std::map<int, int>& came_from, DataProcessor& data);
};