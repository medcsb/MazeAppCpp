#include "headers/maze.hpp"
// Constructor
Maze::Maze(int rows, int cols)
    : rows(rows), cols(cols) {
    setUpEmptyMaze();
    }
void Maze::setUpEmptyMaze() {
    boxes.reserve(rows);
    for (int i = 0; i < rows; i++) {
        vector<MazeBox> row;
        row.reserve(cols);
        for (int j = 0; j < cols; j++) {
            row.emplace_back(MazeBox(i, j, '*'));
        }
        boxes.push_back(move(row));
    }
}
// Methods *********************************************************************

void Maze::printMaze() const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << boxes[i][j].getType() << " ";
        }
        cout << endl;
    }
}

bool Maze::isOutOfBound(int x, int y) const {
    return x <= 0 || x >= rows || y <= 0 || y >= cols;
}

const vector<MazeBox>& Maze::getNeighbors(MazeBox& box) const {
    vector<MazeBox> neighbours;
    addNeighbour(box.getX() - 1, box.getY(), neighbours);
    addNeighbour(box.getX() + 1, box.getY(), neighbours);
    addNeighbour(box.getX(), box.getY() - 1, neighbours);
    addNeighbour(box.getX(), box.getY() + 1, neighbours);
    return neighbours;
}

void Maze::addNeighbour(int x, int y, vector<MazeBox>& neighbours) const {
    if (!isOutOfBound(x, y)) {
        neighbours.push_back(boxes[x][y]);
    }
}

void Maze::saveToFile(const string& fileName) const {
    ofstream file(fileName);
    if (file.is_open()) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                file << boxes[i][j].getType();
            }
            file << endl;
        }
        file.close();
    }
}

void Maze::loadFromFile(const string& fileName) {
    ifstream file(fileName);
    if (file.is_open()) {
        string line;
        int i = 0;
        while (getline(file, line)) {
            for (int j = 0; j < line.size(); j++) {
                boxes[i][j].setType(line[j]);
            }
            i++;
        }
        file.close();
    }
}

string Maze::to_string() const {
    string mazeStr = "";
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
int Maze::getHeight() const {
    return rows;
}
int Maze::getWidth() const {
    return cols;
}
const vector<vector<MazeBox>>& Maze::getBoxes() const {
    return boxes;
}
const MazeBox& Maze::getBox(int x, int y) const {
    return boxes[x][y];
}

// Setters
void Maze::setBox(int row, int col, const char& type) {
    boxes[row][col].setType(type);
}