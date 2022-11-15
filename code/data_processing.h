#include <algorithm>
#include <vector>
#include <map>
#include <string>

using namespace std;
class DataProcessor {
    public:
    // pass file location of movies.dat
    DataProcessor(string movies_id_name);

    // pass file location of movies.dat and ratings.dat
    DataProcessor(string movies_id_name, string reviews_name);

    // writes an adjacency list to the specified file
    void listToFile(string filename, map<int, map<int, int>> list);

    // builds an adjacency list from thte specified file
    void fileToList(string filename, map<int, map<int, int>>& list);


    // attempt to preprocess weights. i realised after running that it was probably slower to save
    // and load the preprocessed data than to just do it every time.
    // If you want to save preprocessed data in some way, find a sparse way to save the adj matrix.
    // vector<vector<int>> reviewsToWeight(vector<string> reviews);
    // void preprocessData(string reviews_name, string target_file);

    // maps a movie id to a pair. first is title, second is position in adjacency matrix.
    map<int, pair<string, int>> movie_id_dict_;

    // adj_list[target][dest] gives us the weight between target and dest
    map<int, map<int, int>> adj_list;


    // Note adj_list[i][j]/num_weights[i][j] = avgweight[i][j]
    // num_weights_list[target][dest] gives the total number of weights between target and test
    map<int, map<int, int>> num_weights_list;

    // number of unique movies
    int num_movies_;

    vector<string> my_id_to_title_;
    
    private:
    // void saveVec(vector<vector<int>> inp, ofstream& target_file);
    void reviewsToList(vector<string> reviews);
};