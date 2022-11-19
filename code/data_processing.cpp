#include "data_processing.h"

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <sstream>

using namespace std;

DataProcessor::DataProcessor(string movies_id_name) {
  ifstream movie_id_file(movies_id_name);
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

DataProcessor::DataProcessor(string movies_id_name, string reviews_name) {
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
  cout << "BBBBB" << endl;

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

// returns the index in the adjacency list of the movie title
int DataProcessor::titleToID(string title) {
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
  pair<string, int> movie = movie_id_dict_[id];
  return movie.first;
}

void DataProcessor::listToFile(string filename, map<int, map<int, int>> list) {
  ofstream os(filename);
  int map_num = 1;
  cout << "Maps written: " << endl;

  for (auto& node : list) {
    // first line of each outer key formatted as "outer_key:{"
    os << node.first << ':' << '{' << '\n';

    // each line of inner map formatted as "inner_key:inner_value"
    for (auto& neighbor : node.second) {
      os << neighbor.first << ':' << neighbor.second << "\n";
    }

    // end of inner map
    os << "}\n";

    // print count at the end of each map write
    stringstream print;
    print << map_num;
    cout << "\r" << print.str();
    map_num++;
  }
  os.close();
}

void fileToList(string filename, map<int, map<int, int>>& list) {
  ifstream ifs(filename);
  int map_num = 1;
  cout << "Maps read: " << endl;
  string line;
  if (ifs.is_open()) {
    while (getline(ifs, line)) {
      if (line.find('{') != string::npos) {
        // extract outer key and add to the outer map with an empty inner map
        size_t o_key_end = line.find(':');
        int outer_key = stoi(line.substr(0, o_key_end));
        list[outer_key] = map<int, int>();

        while (getline(ifs, line)) {
          // extrct ech key-vlue pir of the inner mp
          if (line.find('}') != string::npos) {
            break;
          }
          size_t demarc = line.find(':');
          int inner_key = stoi(line.substr(0, demarc));
          int value = stoi(line.substr(demarc + 1));

          // insert key and value into the inner map
          list[outer_key][inner_key] = value;
        }
        // print count at the end of each map write
        stringstream print;
        print << map_num;
        cout << "\r" << print.str();
        map_num++;
      }
    }
  }
}
