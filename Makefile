CC=clang++
OBJS=main.cpp parser.cpp transition_table.cpp
TARGET=main

all:
	$(CC) $(OBJS) -std=c++17 -o $(TARGET)

debug:
	$(CC) $(OBJS) -std=c++17 -g -o $(TARGET)

run: all
	./$(TARGET)

format:
	clang-format -i lexical_parser.hpp main.cpp state.hpp token.hpp transition_table.hpp transition_table.cpp parser.hpp parser.cpp
