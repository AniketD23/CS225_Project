#include <algorithm>
#include <map>
#include <string>
#include <vector>
#pragma once

using namespace std;
class DataProcessor {
 public:
  // default constructor
  DataProcessor();

  // pass file location of movies.dat and ratings.dat
  DataProcessor(string movies_id_name, string reviews_name);

  // writes an adjacency list to the specified file
  void listToFile(string filename, map<int, map<int, int>> list);

  // builds an adjacency list from the specified file
  void fileToList(string filename, map<int, map<int, int>>& list);

  // writes an adjacency list to the specified file
  void listToFile(string filename, map<int, map<int, double>> list);

  // builds an adjacency list from the specified file
  void fileToListDouble(string filename, map<int, map<int, double>>& list);

  // returns a vector containing the ids of the neighbors of target
  map<int, double> getNeighbors(int target);

  // returns the index in the adjacency list of the movie title
  int titleToID(string title);

  // returns a movie title given an adjacency list ID
  string IDToTitle(int id);

  void populateAvgAdj();

  // attempt to preprocess weights. i realised after running that it was
  // probably slower to save and load the preprocessed data than to just do it
  // every time. If you want to save preprocessed data in some way, find a
  // sparse way to save the adj matrix. vector<vector<int>>
  // reviewsToWeight(vector<string> reviews); void preprocessData(string
  // reviews_name, string target_file);

  // adj_list[target][dest] is the average difference in reviews between target
  // and dest
  map<int, map<int, double>> avg_adj_list_;

  // maps movie id to a pair. first is title, second is position in adjacency
  // matrix.
  map<int, pair<string, int>> movie_id_dict_;

  /**
   * adj_list[target][dest] gives us the sum of the differences in ratings
   * between target and dest (weights), adj_list[target] gives us a map of the
   * adjacent movies
   */
  map<int, map<int, int>> adj_list;

  // num_weights_list[target][dest] gives the total number of ratings between
  // target and dest
  map<int, map<int, int>> num_weights_list;

  // number of unique movies
  int num_movies_;

  vector<string> my_id_to_title_;

 private:
  // void saveVec(vector<vector<int>> inp, ofstream& target_file);
  void reviewsToList(vector<string> reviews);

  // returns true if the edge meets our criteria for to be written
  bool isValidEdge(int node1, int node2);
};
