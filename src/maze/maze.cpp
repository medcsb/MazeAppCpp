#include "headers/maze.hpp"
// Constructor
Maze::Maze(unsigned short rows, unsigned short cols)
    : rows(rows), cols(cols) {
    setUpEmptyMaze();
    }

Maze::Maze() : rows(0), cols(0), boxes() {}

void Maze::setUpEmptyMaze() {
    boxes.reserve(rows);
    for (unsigned short i = 0; i < rows; i++) {
        std::vector<MazeBox> row;
        row.reserve(cols);
        for (unsigned short j = 0; j < cols; j++) {
            row.emplace_back(MazeBox(i, j, '*'));
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

const std::vector<MazeBox> Maze::getNeighbours(const MazeBox& box) const {
    std::vector<MazeBox> neighbours;
    addNeighbour(box.getX(), box.getY() - 1, neighbours); // Left
    addNeighbour(box.getX() - 1, box.getY(), neighbours); // Up
    addNeighbour(box.getX(), box.getY() + 1, neighbours); // Right
    addNeighbour(box.getX() + 1, box.getY(), neighbours); // Down
    return neighbours;
}

void Maze::addNeighbour(unsigned short x, unsigned short y, std::vector<MazeBox>& neighbours) const {
    x = static_cast<int>(x);
    y = static_cast<int>(y);
    if (!isOutOfBound(x, y)) {
        neighbours.push_back(boxes[x][y]);
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
    std::ofstream file(filename, std::ios::binary);
    int rows = this->getHeight();
    int cols = this->getWidth();
    file.write(reinterpret_cast<const char*>(&rows), sizeof(rows));
    file.write(reinterpret_cast<const char*>(&cols), sizeof(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            char type = this->boxes[i][j].getType();
            file.write(&type, sizeof(type));
        }
    }
}

void Maze::loadRawBinary(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    int rows, cols;
    file.read(reinterpret_cast<char*>(&rows), sizeof(rows));
    file.read(reinterpret_cast<char*>(&cols), sizeof(cols));

    // Reinitialize the maze with the new size
    *this = Maze(rows, cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            char type;
            file.read(&type, sizeof(type));
            this->boxes[i][j].setType(type);
        }
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
unsigned short Maze::getHeight() const {
    return rows;
}
unsigned short Maze::getWidth() const {
    return cols;
}
const std::vector<std::vector<MazeBox>>& Maze::getBoxes() const {
    return boxes;
}
const MazeBox& Maze::getBox(unsigned short x, unsigned short y) const {
    return boxes[x][y];
}

const MazeBox& Maze::getBox(int x, int y) const {
    return boxes[x][y];
}

// Setters
void Maze::setBox(unsigned short row, unsigned short col, const char& type) {
    boxes[row][col].setType(type);
}