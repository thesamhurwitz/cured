INCLUDES = -I.
CC = g++
RM = rm
CPPFLAGS = -Wall -std=c++0x

.PHONY: all main clean 

all: main examples

# Sandbox
main: main.out

main.out: main.cpp cured.h
	$(CC) $(INCLUDES) $(CPPFLAGS) -o $@ $^

# Examples
EXAMPLES = $(patsubst examples/%.cpp,%.out,$(wildcard examples/*.cpp))

examples: $(EXAMPLES)

$(EXAMPLES): %.out : examples/%.cpp
	$(CC) $(INCLUDES) $(CPPFLAGS) -o $@ $^

clean:
	$(RM) *.out
