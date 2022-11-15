#include "data_processing.h"
#include <iostream>
#include <fstream>

int main() {
    std::cout << "Start processing" << std::endl;
    DataProcessor d("../data/movies.dat", "../data/ratings.dat");
    std::cout << "\nFinish processing\n" << std::endl;

    // std::cout << "Start writing" << std::endl;
    // d.listToFile("../lists/adj_list.txt", d.adj_list);
    // std::cout << "\nFinish writing\n" << std::endl;

    return 0;
}