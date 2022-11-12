#include "data_processing.h"
#include <iostream>

int main() {
    std::cout << "A" << std::endl;
    DataProcessor d("../data/movies.dat", "../data/ratings.dat");
    // d.preprocessData( "../data/ratings.dat", "../data/weights.txt");
    return 0;
}