#include <iostream>

#include "a_star.h"
#include "data_processing.h"
#include "prim.h"
#pragma once
using namespace std;
class UserInput {
 private:
  string title1;
  string title2;
  string algorithm;

 public:
  UserInput() = default;
  UserInput(char** input);
  string getTitle1();
  string getTitle2();
};
