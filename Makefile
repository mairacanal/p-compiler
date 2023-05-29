CC=clang++
OBJS=main.cpp
TARGET=main

all:
	$(CC) $(OBJS) -std=c++17 -o $(TARGET)

run: all
	./$(TARGET)

format:
	clang-format -i lexical_parser.hpp main.cpp state.hpp token.hpp transition_table.hpp
