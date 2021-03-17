#include <iostream>

#define CURED_IMPLEMENTATION
#include "../cured.h"

int main() {
  Screen screen;

  int width = screen.getWidth();
  int height = screen.getHeight();

  int x = 2, y = 2;
  for (auto c : "Underlined") {
    screen.at(x, y) = c;
    screen.charAt(x++, y).Underlined = true;
  }
  x = 2; y++;
  for (auto c : "Inverted") {
    screen.at(x, y) = c;
    screen.charAt(x++, y).Inverted = true;
  }
  x = 2; y++;
  for (auto c : "Dim") {
    screen.at(x, y) = c;
    screen.charAt(x++, y).Dim = true;
  }
  x = 2; y++;
  for (auto c : "Bold") {
    screen.at(x, y) = c;
    screen.charAt(x++, y).Bold = true;
  }
  x = 2; y++;
  for (auto c : "Blink") {
    screen.at(x, y) = c;
    screen.charAt(x++, y).Blink = true;
  }


  screen.Draw();



  Terminal::restore();
  // int a;
  // std::cin >> a;
}