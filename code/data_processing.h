#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <unordered_map>
#pragma once

using namespace std;
class DataProcessor {
 public:
  // default constructor. pass id_list_filename = "test" to use a test set of ids
  DataProcessor(string id_list_filename, string adj_list_filename);
  
  // blank dataset for testing
  DataProcessor();

  // loads entire dataset from given filenames
  void loadReviewsToAdjList(string movies_id_name, string reviews_name);

  // writes an adjacency list to the specified file
  void listToFile(string filename, unordered_map<int, unordered_map<int, double>>& list);

  // builds an adjacency list from the specified file
  void fileToListDouble(string filename, unordered_map<int, unordered_map<int, double>>& list);

  // returns a vector containing the ids of the neighbors of target
  unordered_map<int, double> getNeighbors(int target);

  // returns the index in the adjacency list of the movie title
  int titleToID(string title);

  // returns a movie title given an adjacency list ID
  string IDToTitle(int id);

  void populateAvgAdj();


  // adj_list[target][dest] is the average difference in reviews between target
  // and dest
  unordered_map<int, unordered_map<int, double>> avg_adj_list_;

  // maps movie id to a pair. first is title, second is position in adjacency
  // matrix.
  unordered_map<int, pair<string, int>> movie_id_dict_;

  /**
   * adj_list[target][dest] gives us the sum of the differences in ratings
   * between target and dest (weights), adj_list[target] gives us a map of the
   * adjacent movies
   */
  unordered_map<int, unordered_map<int, int>> adj_list;

  // num_weights_list[target][dest] gives the total number of ratings between
  // target and dest
  unordered_map<int, unordered_map<int, int>> num_weights_list;

  // number of unique movies
  int num_movies_;

  vector<string> my_id_to_title_;

 private:
  // void saveVec(vector<vector<int>> inp, ofstream& target_file);
  void reviewsToList(vector<string> reviews);

  // returns true if the edge meets our criteria for to be written
  bool isValidEdge(int node1, int node2);

  bool testing_;

  bool loadIdListFromFile(string filename);
};
