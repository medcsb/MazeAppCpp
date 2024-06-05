#ifndef MAZE_HPP
#define MAZE_HPP

#include "mazeBox.hpp"

#include <iostream>
#include <vector>
#include <fstream>


class Maze{
public:
// Constructor
Maze(ushort rows, ushort cols);
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
ushort getHeight() const;
ushort getWidth() const;
const std::vector<std::vector<MazeBox>>& getBoxes() const;
const MazeBox& getBox(ushort x, ushort y) const;
const MazeBox& getBox(int x, int y) const;
Coords getStart() const;
Coords getEnd() const;
// Setters
void setBox(ushort x, ushort y, const char& type);

private:
    ushort rows;
    ushort cols;
    std::vector<std::vector<MazeBox>> boxes;
    Coords start;
    Coords end;
};

#endif // MAZE_HPP
