#ifndef MAZE_HPP
#define MAZE_HPP

#include "mazeBox.hpp"

#include <iostream>
#include <vector>
#include <fstream>


class Maze{
public:
// Constructor
Maze(unsigned short rows, unsigned short cols);
Maze();

void setUpEmptyMaze();
// Methods *********************************************************************

void printMaze() const;
const std::vector<MazeBox> getNeighbours(int x, int y) const;
const std::vector<Coords> getNeighboursCoords(int x, int y) const;
void addNeighbour(int x, int y, std::vector<MazeBox>& neighbours) const;
void addNeighbour(int x, int y, std::vector<Coords>& neighbours) const;
bool isOutOfBound(int x, int y) const;
void saveToFile(const std::string& fileName) const;
void loadFromFile(const std::string& fileName);
void saveRawBinary(const std::string& fileName) const;
void loadRawBinary(const std::string& fileName);
std::string to_string() const;

// Methods *********************************************************************
// Getters
unsigned short getHeight() const;
unsigned short getWidth() const;
const std::vector<std::vector<MazeBox>>& getBoxes() const;
const MazeBox& getBox(unsigned short x, unsigned short y) const;
const MazeBox& getBox(int x, int y) const;
// Setters
void setBox(unsigned short x, unsigned short y, const char& type);

private:
    unsigned short rows;
    unsigned short cols;
    std::vector<std::vector<MazeBox>> boxes;
};

#endif // MAZE_HPP
