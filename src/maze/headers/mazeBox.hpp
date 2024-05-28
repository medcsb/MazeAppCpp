#ifndef MAZEBOX_HPP
#define MAZEBOX_HPP


struct Coords{
    unsigned short x;
    unsigned short y;
    // overloaded operator to compare two Coords
    bool operator==(const Coords& other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Coords& other) const {
        return x != other.x || y != other.y;
    }
};

class MazeBox {
public:
    // Constructor
    MazeBox(const char& type);
    // Getters
    char getType() const;
    // Setters
    void setType(const char& type);

private:
    char type; // '#' for wall, 'S' for start, 'E' for end, '*' for empty
};

#endif // MAZEBOX_HPP