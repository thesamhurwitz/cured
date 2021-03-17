#include <iostream>

#define CURED_IMPLEMENTATION
#include "cured.h"

int main() {
  Screen screen;

  for (int i = 1; i < 8; i++) {
    for (int j = 3; j < 7; j++) {
      screen.at(i, j) = U'🍌';

      if (i % 2 == 0 && j % 2 == 0) {
        screen.charAt(i, j).Inverted = true;
      }
    }
  }

  screen.Draw();



  Terminal::restore();
  // int a;
  // std::cin >> a;
}