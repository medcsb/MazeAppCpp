#ifndef MAZEBOX_HPP
#define MAZEBOX_HPP

#include <iostream>

typedef struct {
    int x;
    int y;
} Coords;

class MazeBox {
public:
    // Constructor
    MazeBox(int x, int y, const char& type);
    // Getters
    int getX() const;
    int getY() const;
    Coords getCoords() const;
    char getType() const;
    // Setters
    void setType(const char& type);

private:
    int x; 
    int y;
    char type; // 'W' for wall, 'S' for start, 'E' for end, 'P' for path
    Coords coords;
};

#endif // MAZEBOX_HPP