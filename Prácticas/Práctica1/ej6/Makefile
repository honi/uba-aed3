CC = g++
CPPFLAGS = -g -std=c++11 -Wall -pedantic
OUTPUT_PATH := bin
OUTPUT_FILENAME := app

.PHONY: all clean

all: app

app: main.cpp
	@mkdir -p $(OUTPUT_PATH)
	$(CC) $(CPPFLAGS) $< -o $(OUTPUT_PATH)/$(OUTPUT_FILENAME)

clean:
	rm -f *.o
	rm -rf $(OUTPUT_PATH)
