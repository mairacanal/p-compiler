CC=clang++
OBJS=main.cpp
TARGET=main

all:
	$(CC) $(OBJS) -std=c++17 -o $(TARGET)

run: all
	./$(TARGET)
