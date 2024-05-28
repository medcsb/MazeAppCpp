#ifndef MAZE_HPP
#define MAZE_HPP

#include "mazeBox.hpp"

#include <iostream>
#include <vector>
#include <fstream>


class Maze{
public:
// Constructor
Maze(int rows, int cols);
Maze();

void setUpEmptyMaze();
// Methods *********************************************************************

void printMaze() const;
const std::vector<MazeBox> getNeighbours(const MazeBox& box) const;
void addNeighbour(int x, int y, std::vector<MazeBox>& neighbours) const;
bool isOutOfBound(int x, int y) const;
void saveToFile(const std::string& fileName) const;
void loadFromFile(const std::string& fileName);
void saveRawBinary(const std::string& fileName) const;
void loadRawBinary(const std::string& fileName);
std::string to_string() const;

// Methods *********************************************************************
// Getters
int getHeight() const;
int getWidth() const;
const std::vector<std::vector<MazeBox>>& getBoxes() const;
const MazeBox& getBox(int x, int y) const;
// Setters
void setBox(int x, int y, const char& type);

private:
    int rows;
    int cols;
    std::vector<std::vector<MazeBox>> boxes;
};

#endif // MAZE_HPP
