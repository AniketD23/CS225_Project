#include "a_star.h"
#include <iostream>

vector<string> A_Star::shortestPath(std::string start, std::string end,
                                    DataProcessor& data) {
  int start_id = data.titleToID(start);
  int end_id = data.titleToID(end);

  // came_from[id] gives the id from which this id was accessed.
  std::map<int, int> came_from;

  // g_score[id] gives the cheapest known way to get to id from start
  std::map<int, double> g_score;
  g_score[start_id] = 0;

  // first is distance + heuristic, second is id
  // internet suggests that priority queue by default sorts pairs based on the
  // first.
  priority_queue<std::pair<double, int>, vector<std::pair<double, int>>,
                 CompClass>
      open_queue;

  // open_set keeps track of which ids need to be checked. this circumvents
  // updating the priority queue
  std::set<int> open_set;

  open_queue.push(std::make_pair(
      g_score[start_id] + heuristic(start_id, end_id, data), start_id));
  open_set.insert(start_id);
  while (!open_queue.empty()) {
    // check if the current item is on the list to be checked
    auto set_it = open_set.find(open_queue.top().second);
    while (set_it == open_set.end()) {
      open_queue.pop();
      if (open_queue.empty()) {
        return std::vector<string>();
      }
      set_it = open_set.find(open_queue.top().second);
    }
    int curr_id = open_queue.top().second;
    // std::cout << curr_id << ", " << g_score[curr_id] << std::endl;
    // reached our goal
    if (curr_id == end_id) {
      return backtrack(start_id, end_id, came_from, data);
    }

    open_queue.pop();
    open_set.erase(set_it);
    std::map<int, double> neighbors = data.getNeighbors(curr_id);

    for (auto& n : neighbors) {
      int n_id = n.first;
      double tentative_g_score = g_score[curr_id] + data.avg_adj_list_[curr_id][n_id];
      auto it = g_score.find(n_id);
      if (it == g_score.end() || tentative_g_score < it->second) {
        // std::cout << "A:" << n_id << ", " << tentative_g_score << std::endl;
        g_score[n_id] = tentative_g_score;
        came_from[n_id] = curr_id;
        open_set.insert(n_id);
        open_queue.push(std::make_pair(tentative_g_score + heuristic(n_id, end_id, data), n_id));
      }
    }
  }
  return std::vector<string>();
}

int A_Star::heuristic(int start_id, int end_id, DataProcessor& data) {
  // return 0;
  if (start_id == end_id) {
    return 0;
  }
  if (data.avg_adj_list_[start_id].count(end_id) == 0) {
    return 10;
  }
  return data.avg_adj_list_[start_id][end_id];
}

vector<string> A_Star::backtrack(int start, int end,
                                 std::map<int, int>& came_from,
                                 DataProcessor& data) {
  std::vector<std::string> out;
  int curr = end;
  while (curr != start) {
    out.insert(out.begin(), data.IDToTitle(curr));
    curr = came_from[curr];
  }
  out.insert(out.begin(), data.IDToTitle(start));
  return out;
}
