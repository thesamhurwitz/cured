INCLUDES = -I.
CC = g++
RM = rm
CPPFLAGS = -Wall -std=c++17

.PHONY: all main clean 

all: main examples benchmarks

# Sandbox
main: main.out

main.out: main.cpp cured.h
	$(CC) $(INCLUDES) $(CPPFLAGS) -o $@ $^

# Examples
EXAMPLES = $(patsubst examples/%.cpp,%.out,$(wildcard examples/*.cpp))

examples: $(EXAMPLES)

$(EXAMPLES): %.out : examples/%.cpp
	$(CC) $(INCLUDES) $(CPPFLAGS) -o $@ $^

# Benchmark
BENCHMARKS = $(patsubst benchmarks/%.cpp,%.out,$(wildcard benchmarks/*.cpp))

benchmarks: $(BENCHMARKS)

$(BENCHMARKS): %.out : benchmarks/%.cpp cured.h
	$(CC) $(INCLUDES) $(CPPFLAGS) -o $@ $^ -lbenchmark

clean:
	$(RM) *.out
