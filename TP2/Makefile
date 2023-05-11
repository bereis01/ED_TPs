CXX = g++
CXXFLAGS = -std=c++11 -Wall
MAKE = make

OBJ_DIR = ./obj
SRC_DIR = ./src
INCLUDE_DIR = ./include

TARGET = ./bin/tp2
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
INCLUDE_FILES = $(wildcard $(INCLUDE_DIR)/*.hpp)

all : main

main : $(TARGET)

$(TARGET) : $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp $(INCLUDE_FILES)
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_DIR) -c $< -o $@

clean:
	rm $(OBJ_FILES) $(TARGET)