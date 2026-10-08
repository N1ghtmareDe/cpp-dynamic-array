CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

SRC      = src/DynamicArray.cpp src/main.cpp
OBJ      = $(SRC:.cpp=.o)
TARGET   = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

src/%.o: src/%.cpp include/DynamicArray.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

rebuild: clean all

run: all
	./$(TARGET)

.PHONY: all clean rebuild run