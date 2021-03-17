#include <iostream>

#define CURED_IMPLEMENTATION
#include "../cured.h"

int main() {
  Screen screen;

  int width = screen.getWidth();
  int height = screen.getHeight();

  for (int i = 2; i < width - 3; i++) {
    for (int j = 2; j < height - 3; j++) {
      if (i % 2 == 0 && j % 2 == 0) {
        screen.at(i, j) = U'Ɣ';
        screen.charAt(i, j).Inverted = true;
      } else {
        screen.at(i, j) = U'o';
      }
    }
  }

  screen.Draw();



  Terminal::restore();
  // int a;
  // std::cin >> a;
}