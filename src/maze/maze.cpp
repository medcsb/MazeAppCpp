#include "headers/maze.hpp"
// Constructor
Maze::Maze(ushort rows, ushort cols)
    : rows(rows), cols(cols) {
    setUpEmptyMaze();
    }

Maze::Maze() : rows(0), cols(0), boxes() {}

void Maze::setUpEmptyMaze() {
    boxes.reserve(rows);
    for (ushort i = 0; i < rows; i++) {
        std::vector<MazeBox> row;
        row.reserve(cols);
        for (ushort j = 0; j < cols; j++) {
            row.emplace_back(MazeBox('*'));
        }
        boxes.push_back(move(row));
    }
}
// Methods *********************************************************************

void Maze::printMaze() const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << boxes[i][j].getType() << " ";
        }
        std::cout << std::endl;
    }
}

bool Maze::isOutOfBound(int x, int y) const {
    return x < 0 || x >= rows || y < 0 || y >= cols;
}

const std::vector<MazeBox> Maze::getNeighbours(int x, int y) const {
    std::vector<MazeBox> neighbours;
    addNeighbour(x, y - 1, neighbours); // Left
    addNeighbour(x - 1, y, neighbours); // Up
    addNeighbour(x, y + 1, neighbours); // Right
    addNeighbour(x + 1, y, neighbours); // Down
    return neighbours;
}

const std::vector<Coords> Maze::getNeighboursCoords(int x, int y) const {
    std::vector<Coords> neighbours;
    addNeighbour(x, y - 1, neighbours); // Left
    addNeighbour(x - 1, y, neighbours); // Up
    addNeighbour(x, y + 1, neighbours); // Right
    addNeighbour(x + 1, y, neighbours); // Down
    return neighbours;
}

void Maze::addNeighbour(int x, int y, std::vector<MazeBox>& neighbours) const {
    if (!isOutOfBound(x, y)) {
        neighbours.push_back(boxes[x][y]);
    }
    return;
}

void Maze::addNeighbour(int x, int y, std::vector<Coords>& neighbours) const {
    if (!isOutOfBound(x, y)) {
        neighbours.push_back(Coords{static_cast<ushort>(x), static_cast<ushort>(y)});
    }
    return;
}

void Maze::saveToFile(const std::string& fileName) const {
    std::ofstream file(fileName);
    if (file.is_open()) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                file << boxes[i][j].getType();
            }
            file << std::endl;
        }
        file.close();
    }
}

void Maze::loadFromFile(const std::string& fileName) {
    std::ifstream file(fileName);
    // count rows and cols
    if (file.is_open()) {
        std::string line;
        rows = 0;
        cols = 0;
        while (getline(file, line)) {
            cols = (cols == 0) ? line.size() : cols;
            rows++;
        }
        file.close();
    }
    this->rows = rows;
    this->cols = cols;
    this->setUpEmptyMaze();
    std::ifstream file1(fileName);
    if (file1.is_open()) {
        std::string line;
        int i = 0;
        while (getline(file1, line)) {
            for (int j = 0; j < line.size(); j++) {
                boxes[i][j].setType(line[j]);
            }
            i++;
        }
        file1.close();
    }
}

void Maze::saveRawBinary(const std::string& filename) const {
    std::fstream file(filename, std::ios::binary | std::ios::out);
    if (!file.is_open()) {
        std::cerr << "Error Creating save file" << std::endl;
        return;
    }
    file.write(reinterpret_cast<const char*>(&rows), sizeof(rows));
    file.write(reinterpret_cast<const char*>(&cols), sizeof(cols));
    char type;
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->cols; ++j) {
            type = this->boxes[i][j].getType();
            file.write(&type, sizeof(type));
        }
    }
}

void Maze::loadRawBinary(const std::string& filename) {
    std::fstream file(filename, std::ios::binary | std::ios::in);
    if (!file.is_open()) {
        std::cerr << "Error Opening save file" << std::endl;
        return;
    }
    ushort rows;
    ushort cols;
    file.read(reinterpret_cast<char*>(&rows), sizeof(rows));
    file.read(reinterpret_cast<char*>(&cols), sizeof(cols));
    this->rows = rows;
    this->cols = cols;
    this->boxes.clear();
    this->boxes.reserve(rows);
    for (int i = 0; i < rows; ++i) {
        std::vector<MazeBox> row;
        row.reserve(cols);
        for (int j = 0; j < cols; ++j) {
            char type;
            file.read(&type, sizeof(type));
            row.emplace_back(MazeBox(type));
        }
        this->boxes.push_back(row);
    }
}

std::string Maze::to_string() const {
    std::string mazeStr = "";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mazeStr += boxes[i][j].getType();
        }
        if (i != rows - 1) {
            mazeStr += "\n";
        }
    }
    return mazeStr;
}

// Methods *********************************************************************
// Getters
ushort Maze::getHeight() const {
    return rows;
}
ushort Maze::getWidth() const {
    return cols;
}
const std::vector<std::vector<MazeBox>>& Maze::getBoxes() const {
    return boxes;
}
const MazeBox& Maze::getBox(ushort x, ushort y) const {
    return boxes[x][y];
}

const MazeBox& Maze::getBox(int x, int y) const {
    return boxes[x][y];
}

Coords Maze::getStart() const {
    return start;
}

Coords Maze::getEnd() const {
    return end;
}

// Setters
void Maze::setBox(ushort row, ushort col, const char& type) {
    boxes[row][col].setType(type);
}