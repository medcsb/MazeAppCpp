#ifndef MAZEBOX_HPP
#define MAZEBOX_HPP


typedef struct {
    unsigned short x;
    unsigned short y;
} Coords;

class MazeBox {
public:
    // Constructor
    MazeBox(unsigned short x, unsigned short y, const char& type);
    // Getters
    unsigned short getX() const;
    unsigned short getY() const;
    Coords getCoords() const;
    char getType() const;
    // Setters
    void setType(const char& type);
    // Overload the ==/!= operators
    bool operator==(const MazeBox& other) const;
    bool operator!=(const MazeBox& other) const;

private:
    unsigned short x; // row
    unsigned short y; // col
    char type; // '#' for wall, 'S' for start, 'E' for end, '*' for empty
    Coords coords;
};

#endif // MAZEBOX_HPP