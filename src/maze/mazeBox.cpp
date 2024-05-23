#include "headers/mazeBox.hpp"

// Constructor
MazeBox::MazeBox(int x, int y, const char& type)
    : x(x), y(y), type(type) {
    coords.x = x;
    coords.y = y;
    }
// Methods *********************************************************************

// Methods *********************************************************************
// Getters
int MazeBox::getX() const {
    return x;
}
int MazeBox::getY() const {
    return y;
}
Coords MazeBox::getCoords() const {
    return coords;
}
char MazeBox::getType() const {
    return type;
}
// Setter for type
void MazeBox::setType(const char& type) {
    this->type = type;
}
