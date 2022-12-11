#include "user_input.h"

UserInput::UserInput(char** input) {
  if (!input[1] && !input[2]) {
    std::cout << '\n'
              << "Usage: [algorithm, movie title1, movie title 2]" << std::endl;
  } else {
    algorithm = input[1];
    title1 = input[2];
    title2 = (input[3]) ? (input[3]) : ("");
  }
}

string UserInput::getTitle1() { return title1; }
string UserInput::getTitle2() { return title2; }


/*   DataProcessor d("../data/movies.dat", "../lists/avg_adj_list_.txt");

  std::cout << "\ninitialize bfs" << std::endl;
  BFS bfs(d);
  
  std::cout << "Perform bfs" << std::endl;
  bfs.breadthFirst("The Avengers", "The Lion King");

  std::cout << "\nBFS of size: " << bfs.traversal().size() << std::endl;
  std::ofstream os;
  os.open("../out/BFS_out.txt", std::ofstream::out | std::ofstream::trunc);

  for (std::string e : bfs.traversal()) {
    os << e << '\n';
  }
 */
