#include "data_processing.h"

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <sstream>

using namespace std;

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

  // adj_mat = vector<vector<int>>(new_id+1, vector<int>(new_id+1, 0));
  // num_weights = vector<vector<int>>(new_id+1, vector<int>(new_id+1, 0));
  // cout << "AAAA" << endl;
  int cc = 0;
  ifstream reviews_file(reviews_name);
  if (reviews_file.is_open()) {
    vector<string> reviews_from_same_user;
    int current_user = -1;
    // for (int i = 0; i < 500; i++) {
    while (getline(reviews_file, line)) {
      cout << cc << endl;
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
  // vector<vector<int>> out;
  if (reviews.size() <= 1) {
    return;
  }
  for (int i = 0; i < (int)reviews.size(); i++) {
    for (int j = i + 1; j < (int)reviews.size(); j++) {
      string first = reviews[i];
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

      map<int, pair<string, int>>::iterator it1 = movie_id_dict_.find(first_id);
      map<int, pair<string, int>>::iterator it2 =
          movie_id_dict_.find(second_id);
      if (it1 != movie_id_dict_.end() && it2 != movie_id_dict_.end()) {
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
}

// ignore everything below here
// vector<vector<int>> DataProcessor::reviewsToWeight(vector<string> reviews) {
//     vector<vector<int>> out;
//     for (int i = 0; i < (int) reviews.size(); i++) {
//         for (int j = i+1; j < (int) reviews.size(); j++) {
//             string first = reviews[i];
//             string second = reviews[j];
//             int first_split_ind = first.find("::");
//             int first_id = stoi(first.substr(0, first_split_ind));
//             int first_score = stoi(first.substr(first_split_ind+2,
//             string::npos));
//             // cout << "f_id: " << first_id << ", " <<
//             movie_id_dict_.at(first_id).second << ", " << first_score <<
//             endl;

//             int second_split_ind = second.find("::");
//             int second_id = stoi(second.substr(0, second_split_ind));
//             int second_score = stoi(second.substr(second_split_ind+2,
//             string::npos));
//             // cout << "s_id: " << second_id << ", " <<
//             movie_id_dict_.at(second_id).second << ", " << second_score <<
//             endl; vector<int> r_weight = {first_id, second_id,
//             abs(first_score-second_score)}; out.push_back(r_weight);
//             //
//             adj_mat[movie_id_dict_.at(first_id).second][movie_id_dict_.at(second_id).second]
//             += abs(first_score-second_score);
//             //
//             adj_mat[movie_id_dict_.at(first_id).second][movie_id_dict_.at(second_id).second].first
//             += abs(first_score-second_score);
//             //
//             adj_mat[movie_id_dict_.at(first_id).second][movie_id_dict_.at(second_id).second].second++;
//         }
//     }
//     return out;
// }
// void DataProcessor::saveVec(vector<vector<int>> inp, ofstream& target_file) {
//     for (auto& v : inp) {
//         target_file << v[0] << "," << v[1] << "," << v[2] << endl;
//     }
// }

// void DataProcessor::preprocessData(string reviews_name, string target_name) {
//     ofstream target_file(target_name);
//     ifstream reviews_file(reviews_name);
//     string line;
//     if (reviews_file.is_open() && target_file.is_open()) {
//         vector<string> reviews_from_same_user;
//         int current_user = -1;
//         // for (int i = 0; i < 500; i++) {
//         while (getline(reviews_file, line)) {
//             // getline(reviews_file, line);
//             int first = line.find("::");
//             int last = line.rfind("::");
//             if (current_user != stoi(line.substr(0, first))) {
//                 if (!reviews_from_same_user.empty()) {
//                     saveVec(reviewsToWeight(reviews_from_same_user),
//                     target_file);
//                 }
//                 current_user = stoi(line.substr(0, first));
//                 reviews_from_same_user.clear();
//             }
//             string review = line.substr(first+2, last-first-2);
//             reviews_from_same_user.push_back(review);
//         }
//         if (!reviews_from_same_user.empty()) {
//             saveVec(reviewsToWeight(reviews_from_same_user), target_file);
//         }
//     }

// }
