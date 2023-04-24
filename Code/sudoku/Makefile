CC = g++
CPPFLAGS = -g -std=c++14 -Wall -pedantic

app: main.cpp
	@mkdir -p bin
	$(CC) $(CPPFLAGS) $< -o bin/app

clean:
	rm -rf bin

.PHONY: clean
