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
