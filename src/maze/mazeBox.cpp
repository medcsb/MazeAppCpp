#include "headers/mazeBox.hpp"

// Constructor
MazeBox::MazeBox(const char& type) : type(type) {}
// Methods *********************************************************************

// Methods *********************************************************************
// Getters

char MazeBox::getType() const {
    return type;
}
// Setter for type
void MazeBox::setType(const char& type) {
    this->type = type;
}