#include <benchmark/benchmark.h>

#define CURED_IMPLEMENTATION
#include "../cured.h"

static void BM_Full(benchmark::State& state) {
  for (auto _ : state) {
    Screen screen;

    for (int i = 1; i < 8; i++) {
      for (int j = 3; j < 7; j++) {
        screen.at(i, j) = U'*';
      }
    }

    screen.Draw();

    Terminal::restore();
  }
}

BENCHMARK(BM_Full);

static void BM_Draw(benchmark::State& state) {
  Screen screen;

  for (int i = 1; i < 8; i++) {
    for (int j = 3; j < 7; j++) {
      screen.at(i, j) = U'*';
    }
  }
  
  for (auto _ : state) {
    screen.Draw();
  }

  Terminal::restore();
}

BENCHMARK(BM_Draw);

static void BM_Draw_UTF8(benchmark::State& state) {
  Screen screen;

  for (int i = 1; i < 8; i++) {
    for (int j = 3; j < 7; j++) {
      screen.at(i, j) = U'Ɣ';
    }
  }
  
  for (auto _ : state) {
    screen.Draw();
  }

  Terminal::restore();
}

BENCHMARK(BM_Draw_UTF8);

static void BM_Draw_Emoji(benchmark::State& state) {
  Screen screen;

  for (int i = 1; i < 8; i++) {
    for (int j = 3; j < 7; j++) {
      screen.at(i, j) = U'🍌';
    }
  }
  
  for (auto _ : state) {
    screen.Draw();
  }

  Terminal::restore();
}

BENCHMARK(BM_Draw_Emoji);

static void BM_Draw_SGR(benchmark::State& state) {
  Screen screen;

  for (int i = 1; i < 8; i++) {
    for (int j = 3; j < 7; j++) {
      screen.at(i, j) = U'🍌';

      if (i % 2 == 0 && j % 2 == 0) {
        screen.charAt(i, j).Inverted = true;
      }
    }
  }
  
  for (auto _ : state) {
    screen.Draw();
  }

  Terminal::restore();
}

BENCHMARK(BM_Draw_SGR);


static void BM_Draw_Color(benchmark::State& state) {
  Screen screen;

  for (int i = 1; i < 8; i++) {
    for (int j = 3; j < 7; j++) {
      screen.at(i, j) = U'*';

      if (i % 2 == 0 && j % 2 == 0) {
        screen.charAt(i, j).ForegroundColor = Color::Blue;
        screen.charAt(i, j).BackgroundColor = Color::Yellow;
      } else {
        screen.charAt(i, j).ForegroundColor = Color::Cyan;
        screen.charAt(i, j).BackgroundColor = Color::White;
      }
    }
  }
  
  for (auto _ : state) {
    screen.Draw();
  }

  Terminal::restore();
}

BENCHMARK(BM_Draw_Color);

BENCHMARK_MAIN();