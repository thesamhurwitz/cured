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


BENCHMARK_MAIN();