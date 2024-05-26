#ifndef MAZEBOX_HPP
#define MAZEBOX_HPP


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
    // Overload the ==/!= operators
    bool operator==(const MazeBox& other) const;
    bool operator!=(const MazeBox& other) const;

private:
    int x; // row
    int y; // col
    char type; // '#' for wall, 'S' for start, 'E' for end, '*' for empty
    Coords coords;
};

#endif // MAZEBOX_HPP