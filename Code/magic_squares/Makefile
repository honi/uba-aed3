CC = g++
CPPFLAGS = -g -std=c++11 -Wall -pedantic
OUTPUT_PATH := bin

.PHONY: all clean

all: benchmark

benchmark: naive optimized
	@time $(OUTPUT_PATH)/naive 3
	@time $(OUTPUT_PATH)/optimized 3

naive: main_naive.cpp
	@mkdir -p $(OUTPUT_PATH)
	$(CC) $(CPPFLAGS) $< -o $(OUTPUT_PATH)/naive

optimized: main_optimized.cpp
	@mkdir -p $(OUTPUT_PATH)
	$(CC) $(CPPFLAGS) $< -o $(OUTPUT_PATH)/optimized

clean:
	rm -f *.o
	rm -rf $(OUTPUT_PATH)
