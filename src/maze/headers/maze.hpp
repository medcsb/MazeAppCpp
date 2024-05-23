#ifndef MAZE_HPP
#define MAZE_HPP

#include "mazeBox.hpp"

#include <vector>
#include <fstream>
using namespace std;

class Maze{
public:
// Constructor
Maze(int rows, int cols);
void setUpEmptyMaze();
// Methods *********************************************************************

void printMaze() const;
const vector<MazeBox>& getNeighbors(MazeBox& box) const;
void addNeighbour(int x, int y, vector<MazeBox>& neighbours) const;
bool isOutOfBound(int x, int y) const;
void saveToFile(const string& fileName) const;
void loadFromFile(const string& fileName);
string to_string() const;

// Methods *********************************************************************
// Getters
int getHeight() const;
int getWidth() const;
const vector<vector<MazeBox>>& getBoxes() const;
const MazeBox& getBox(int x, int y) const;
// Setters
void setBox(int x, int y, const char& type);

private:
    int rows;
    int cols;
    vector<vector<MazeBox>> boxes;
};

#endif // MAZE_HPP
