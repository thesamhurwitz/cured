#include <iostream>

#define CURED_IMPLEMENTATION
#include "cured.h"

int main() {
  Screen screen;
  screen.Init();

  for (int i = 1; i < 8; i++) {
    for (int j = 3; j < 7; j++) {
      screen.at(i, j) = '*';
    }
  }

  screen.Draw();



  Terminal::restore();
  // int a;
  // std::cin >> a;
}