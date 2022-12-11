#include <fstream>
#include <iostream>
#include <sstream>

#include "data_processing.h"
<<<<<<< HEAD
#include "bfs.h"


int main() {
=======
#include "user_input.h"

int main(int argc, char** argv) {
  DataProcessor d("../data/movies.dat", "../lists/avg_adj_list_.txt");
>>>>>>> 5e8039b84da0d4c258886f8c26c4dade821251bc

  DataProcessor proc;
  proc.fileToListDouble("../lists/bfs_test.txt", proc.avg_adj_list_);
  BFS bfs(proc);

  bfs.breadthFirst("0");

  std::cout << "\nBFS:" << std::endl;

  for (std::string e : bfs.traversal()) {
    std::cout << e << std::endl;
  }

<<<<<<< HEAD

  // DataProcessor d("../data/movies.dat", "../lists/avg_adj_list_.txt");

  // std::map<int, double> neighborhood = d.getNeighbors(56);
  // std::cout << '\n';

  // for (auto& e : neighborhood) {
  //   std::cout << e.first << " : " << e.second << std::endl;
  // }


=======
>>>>>>> 5e8039b84da0d4c258886f8c26c4dade821251bc
  // std::cout << "Start reading adj_list" << std::endl;
  // d.fileToList("../lists/adj_list.txt", d.adj_list);
  // std::cout << "\nFinish reading adj_list\n" << std::endl;

  // std::cout << "adj_list[56][134] (should be 5): " << d.adj_list[56][134] <<
  // '\n' << std::endl;

  // std::cout << "Start reading num_weights_list" << std::endl;
  // d.fileToList("../lists/num_weights_list.txt", d.num_weights_list);
  // std::cout << "\nFinish reading num_weights_list\n" << std::endl;

  // std::cout << "num_weights_list[56][134] (should be 3): " <<
  // d.num_weights_list[56][134] << '\n' << std::endl;

  // std::cout << "Start populating avg_adj_list_" << std::endl;
  // d.populateAvgAdj();
  // std::cout << "\nFinish populating avg_adj_list_\n" << std::endl;

<<<<<<< HEAD
  // std::cout << "avg_adj_list_[56][134] (should be 1.66667): " << d.avg_adj_list_[56][134] << '\n' << std::endl;
=======
  std::cout << "avg_adj_list_[56][134] (should be 1.66667): "
            << d.avg_adj_list_[56][134] << '\n'
            << std::endl;
>>>>>>> 5e8039b84da0d4c258886f8c26c4dade821251bc

  // std::cout << "Start writing avg_adj_list_" << std::endl;
  // d.listToFile("../lists/avg_adj_list_.txt", d.avg_adj_list_);
  // std::cout << "\nFinish writing avg_adj_list_\n" << std::endl;

  // std::cout << "Start processing" << std::endl;
  // DataProcessor d("../data/movies.dat", "../data/ratings.dat");
  // std::cout << "\nFinish processing\n" << std::endl;

  // std::vector<int> checked;
  // int edges = 0;
  // int max = 0;
  // for (auto& kv1 : d.num_weights_list) {
  //   for (auto& kv2 : kv1.second) {
  //     if (find(checked.begin(), checked.end(), kv2.first) != checked.end()) {
  //       if (kv2.second > 2) {
  //         edges++;
  //         if (kv2.second > max) {
  //           max = kv2.second;
  //         }
  //       }
  //     }
  //   }
  //   checked.push_back(kv1.first);
  // }

  // std::cout << "edges with 3 or more reviews: " << edges << std::endl;
  // std::cout << "max reviews on an edge: " << max << std::endl;

  // std::cout << "Start writing num_weights_list" << std::endl;
  // d.listToFile("../lists/num_weights_list.txt", d.num_weights_list);
  // std::cout << "\nFinish writing num_weights_list\n" << std::endl;

  // std::cout << "Start writing adj_list" << std::endl;
  // d.listToFile("../lists/adj_list.txt", d.adj_list);
  // std::cout << "\nFinish writing adj_list\n" << std::endl;
  UserInput ui(argv);
  std::cout << ui.getTitle1() << std::endl;
  std::cout << ui.getTitle2() << std::endl;
  return 0;
}
