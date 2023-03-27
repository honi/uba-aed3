CC = g++
CPPFLAGS = -g -std=c++11 -Wall -pedantic
LDFLAGS = -g

OUTPUT_PATH := bin
OUTPUT_FILENAME := app
SRC := $(wildcard *.cpp)
HEADERS := $(wildcard *.h)
OBJS := $(patsubst %.cpp,%.o,$(SRC))

.PHONY: all valgrind clean

all: app

app: $(OBJS)
	@mkdir -p $(OUTPUT_PATH)
	$(CC) $(LDFLAGS) $^ -o $(OUTPUT_PATH)/$(OUTPUT_FILENAME)

%.o: %.cpp $(HEADERS)
	$(CC) $(CPPFLAGS) -c $< -o $@

valgrind: app
	valgrind --leak-check=full --track-origins=yes $(OUTPUT_PATH)/$(OUTPUT_FILENAME) grids/01.txt

clean:
	rm -f *.o
	rm -rf $(OUTPUT_PATH)
