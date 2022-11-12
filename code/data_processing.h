#include <algorithm>
#include <vector>
#include <map>
#include <string>

using namespace std;
class DataProcessor {
    public:
    // pass file location of movies.dat and ratings.dat
    DataProcessor(string movies_id_name, string reviews_name);

    // attempt to preprocess weights. i realised after running that it was probably slower to save
    // and load the preprocessed data than to just do it every time.
    // If you want to save preprocessed data in some way, find a sparse way to save the adj matrix.
    // vector<vector<int>> reviewsToWeight(vector<string> reviews);
    // void preprocessData(string reviews_name, string target_file);

    // maps a movie id to a pair. first is title, second is position in adjacency matrix.
    map<int, pair<string, int>> movie_id_dict_;

    // adj_mat[i][j] is the sum of weights between movie i and movie j
    // vector<vector<int>> adj_mat;
    // adj_list[target][dest] gives us the weight between target and dest
    map<int, map<int, int>> adj_list;


    // num_weights[i][j] is the total number of weights between i and j. Note adj_mat[i][j]/num_weights[i][j] = avgweight[i][j]
    // vector<vector<int>> num_weights;
    map<int, map<int, int>> num_weights_list;

    // number of unique movies
    int num_movies_;

    vector<string> my_id_to_title_;
    
    private:
    // void saveVec(vector<vector<int>> inp, ofstream& target_file);
    void reviewsToList(vector<string> reviews);
};