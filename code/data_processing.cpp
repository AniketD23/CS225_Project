#include "data_processing.h"

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <sstream>

using namespace std;
DataProcessor::DataProcessor() {
  testing_ = true;
}

DataProcessor::DataProcessor(string id_list_filename, string adj_list_filename) {
  testing_ = id_list_filename == "test";
  if (!testing_) {
    ifstream movie_id_file(id_list_filename);
    string line;
    int new_id = 0;
    if (movie_id_file.is_open()) {
      while (getline(movie_id_file, line)) {
        int first = line.find("::");
        int last = line.rfind("::");
        int movie_id = stoi(line.substr(0, first));
        string title = line.substr(first + 2, last - first - 2);
        movie_id_dict_[movie_id] = make_pair(title, new_id);
        new_id++;
      }
    }
    num_movies_ = new_id + 1;
    my_id_to_title_ = vector<string>(num_movies_);
    for (auto& m : movie_id_dict_) {
      my_id_to_title_[m.second.second] = m.second.first;
    }
  }

  cout << "Loading adjacency list" << endl;
  fileToListDouble(adj_list_filename, avg_adj_list_);

}

map<int, double> DataProcessor::getNeighbors(int target) {
  return avg_adj_list_[target];
}

void DataProcessor::loadReviewsToAdjList(string movies_id_name, string reviews_name) {

  ifstream movie_id_file(movies_id_name);
  string line;
  int new_id = 0;
  if (movie_id_file.is_open()) {
    while (getline(movie_id_file, line)) {
      int first = line.find("::");
      int last = line.rfind("::");
      movie_id_dict_[stoi(line.substr(0, first))] =
          make_pair(line.substr(first + 2, last - first - 2), new_id);
      new_id++;
      // cout << new_id << endl;
    }
  }
  num_movies_ = new_id + 1;
  my_id_to_title_ = vector<string>(num_movies_);
  for (auto& m : movie_id_dict_) {
    my_id_to_title_[m.second.second] = m.second.first;
  }

  int cc = 0;
  ifstream reviews_file(reviews_name);
  if (reviews_file.is_open()) {
    vector<string> reviews_from_same_user;
    int current_user = -1;
    cout << "Reviews processed: " << endl;
    while (getline(reviews_file, line)) {
      // print count at the start of each review
      stringstream print;
      print << cc;
      cout << "\r" << print.str();
      cc++;

      // getline(reviews_file, line);
      int first = line.find("::");
      int last = line.rfind("::");
      if (current_user != stoi(line.substr(0, first))) {
        if (!reviews_from_same_user.empty()) {
          reviewsToList(reviews_from_same_user);
        }
        current_user = stoi(line.substr(0, first));
        reviews_from_same_user.clear();
      }
      string review = line.substr(first + 2, last - first - 2);
      reviews_from_same_user.push_back(review);
    }
    if (!reviews_from_same_user.empty()) {
      reviewsToList(reviews_from_same_user);
    }
  }
}

void DataProcessor::reviewsToList(vector<string> reviews) {
  if (reviews.size() <= 1) {
    return;
  }
  for (int i = 0; i < (int)reviews.size(); i++) {
    string first = reviews[i];
    for (int j = i + 1; j < (int)reviews.size(); j++) {
      string second = reviews[j];
      int first_split_ind = first.find("::");
      int first_id = stoi(first.substr(0, first_split_ind));
      int first_score = stoi(first.substr(first_split_ind + 2, string::npos));
      // cout << "f_id: " << first_id << ", " <<
      // movie_id_dict_.at(first_id).second << ", " << first_score << endl;

      int second_split_ind = second.find("::");
      int second_id = stoi(second.substr(0, second_split_ind));
      int second_score =
          stoi(second.substr(second_split_ind + 2, string::npos));

      adj_list[movie_id_dict_.at(first_id).second]
              [movie_id_dict_.at(second_id).second] +=
          abs(first_score - second_score);
      adj_list[movie_id_dict_.at(second_id).second]
              [movie_id_dict_.at(first_id).second] +=
          abs(first_score - second_score);
      // adj_mat[movie_id_dict_.at(first_id).second][movie_id_dict_.at(second_id).second]
      // += abs(first_score-second_score);
      // adj_mat[movie_id_dict_.at(second_id).second][movie_id_dict_.at(first_id).second]
      // += abs(first_score-second_score);

      num_weights_list[movie_id_dict_.at(first_id).second]
                      [movie_id_dict_.at(second_id).second] += 1;
      num_weights_list[movie_id_dict_.at(second_id).second]
                      [movie_id_dict_.at(first_id).second] += 1;

      // num_weights[movie_id_dict_.at(first_id).second][movie_id_dict_.at(second_id).second]
      // += 1;
      // num_weights[movie_id_dict_.at(second_id).second][movie_id_dict_.at(first_id).second]
      // += 1;
    }
  }
}

// returns a vector containing the ids of the neighbors of target
// vector<pair<int, int>> DataProcessor::getNeighbors(int target) {
  
// }

// returns the index in the adjacency list of the movie title
int DataProcessor::titleToID(string title) {
  if (testing_) {
    return stoi(title);
  }
  int id = 0;
  for (auto& it : movie_id_dict_) {
    if (it.second.first == title) {
      id = it.second.second;
      break;
    }
  }
  return id;
}

// returns a movie title given an adjacency list ID
string DataProcessor::IDToTitle(int id) {
  if (testing_) {
    return to_string(id);
  }
  pair<string, int> movie = movie_id_dict_[id];
  return movie.first;
}

// int weight for adj_list and num_weights_list
void DataProcessor::listToFile(string filename, map<int, map<int, int>> list) {
  ofstream os(filename);
  int node_num = 0;
  cout << "Nodes written: " << endl;

  for (auto& node : list) {
    // first line of each outer key formatted as "outer_key:{"
    os << node.first << ':' << '{' << '\n';

    // checks if each neighbor has a valid edge and writes to inner map
    // each line of inner map formatted as "inner_key:inner_value"
    for (auto& neighbor : node.second) {
      if (isValidEdge(node.first, neighbor.first)) {
        os << neighbor.first << ':' << neighbor.second << "\n";
      }
    }

    // end of inner map
    os << "}\n";

    // print count at the end of each map write
    stringstream print;
    node_num++;
    print << node_num;
    cout << "\r" << print.str();
  }
  os.close();
}

// double weight for avg_adj_list_
void DataProcessor::listToFile(string filename, map<int, map<int, double>> list) {
  ofstream os(filename);
  int node_num = 0;
  cout << "Nodes written: " << endl;

  for (auto& node : list) {
    if (node.second.empty()) {
      continue;
    }

    // first line of each outer key formatted as "outer_key:{"
    os << node.first << ':' << '{' << '\n';

    // checks if each neighbor has a valid edge and writes to inner map
    // each line of inner map formatted as "inner_key:inner_value"
    for (auto& neighbor : node.second) {
      if (isValidEdge(node.first, neighbor.first)) {
        os << neighbor.first << ':' << neighbor.second << "\n";
      }
    }

    // end of inner map
    os << "}\n";

    // print count at the end of each map write
    stringstream print;
    node_num++;
    print << node_num;
    cout << "\r" << print.str();
  }
  os.close();
}

bool DataProcessor::isValidEdge(int node1, int node2) {
  return num_weights_list[node1][node2] > 2;
}

// int weight for adj_list and num_weights_list
void DataProcessor::fileToList(string filename, map<int, map<int, int>>& list) {
  ifstream ifs(filename);
  int node_num = 1;
  cout << "Nodes read: " << endl;
  string line;
  if (ifs.is_open()) {
    while (getline(ifs, line)) {
      if (line.find('{') != string::npos) {
        // extract outer key and add to the outer map with an empty inner map
        size_t o_key_end = line.find(':');
        int outer_key = stoi(line.substr(0, o_key_end));
        list[outer_key] = map<int, int>();

        while (getline(ifs, line)) {
          // extract each key-value pair of the inner map
          if (line.find('}') != string::npos) {
            break;
          }
          size_t demarc = line.find(':');
          int inner_key = stoi(line.substr(0, demarc));
          int value = stoi(line.substr(demarc + 1));

          // insert key and value into the inner map
          list[outer_key][inner_key] = value;
        }
        // print count at the end of each node read
        stringstream print;
        node_num++;
        print << node_num;
        cout << "\r" << print.str();
      }
    }
  }
}

// double weight for avg_adj_list_
void DataProcessor::fileToListDouble(string filename, map<int, map<int, double>>& list) {
  ifstream ifs(filename);
  int node_num = 1;
  cout << "Nodes read: " << endl;
  string line;
  if (ifs.is_open()) {
    while (getline(ifs, line)) {
      if (line.find('{') != string::npos) {
        // extract outer key and add to the outer map with an empty inner map
        size_t o_key_end = line.find(':');
        int outer_key = stoi(line.substr(0, o_key_end));
        list[outer_key] = map<int, double>();

        while (getline(ifs, line)) {
          // extract each key-value pair of the inner map
          if (line.find('}') != string::npos) {
            break;
          }
          size_t demarc = line.find(':');
          int inner_key = stoi(line.substr(0, demarc));
          double value = stod(line.substr(demarc + 1));

          // insert key and value into the inner map
          list[outer_key][inner_key] = value;
        }
        // print count at the end of each node read
        stringstream print;
        node_num++;
        print << node_num;
        cout << "\r" << print.str();
      }
    }
  }
}

void DataProcessor::populateAvgAdj() {
  vector<int> processed;
  int node_num = 0;
  cout << "Nodes processed: " << endl;
  for (unsigned i = 0; i < adj_list.size(); i++) {
    avg_adj_list_[i] = std::map<int, double>();

    // divide total difference by reviews per edge
    for (auto& kv : adj_list[i]) {
      int j = kv.first;
      if (find(processed.begin(), processed.end(), j) != processed.end()) {
        double weight = 1.0 * adj_list[i][j] / num_weights_list[i][j];
        avg_adj_list_[i][j] = weight;
        avg_adj_list_[j][i] = weight;
      }
    }
    processed.push_back(i);

    // print count at the end of each node write
    stringstream print;
    node_num++;
    print << node_num;
    cout << "\r" << print.str();

  }
}