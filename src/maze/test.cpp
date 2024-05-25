#include "headers/test.hpp"

int main()
{
    // Set console output to UTF-8 on Windows
#ifdef _WIN32
    SET_CONSOLE_UTF8
#endif // _WIN32
    setlocale(LC_ALL, "en_US.UTF-8");
    // **************************************

    // Tests
    testMazeCreation();
    // testMazePrint();
    timeTaken(testMazeString);
    timeTaken(testMazeSave);
    timeTaken(testMazeLoad);
    return 0;
}

void testMazeCreation() {
    timeTaken([]() {
        int rows = 756;
        int cols = 1732;
        Maze maze(rows, cols);
        if (maze.getHeight() != rows || maze.getWidth() != cols) {
            std::cout << "Maze creation failed " << CROSS_EMOJI << std::endl;
            return;
        }
        vector<vector<MazeBox>> boxes = maze.getBoxes();
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (boxes[i][j].getType() != '*') {
                    std::cout << "Wrong type for box (" << i << ", " << j << ") " << CROSS_EMOJI << std::endl;
                    return;
                }
            }
        }
        std::cout << "Empty maze created successfully " << CHECK_EMOJI << std::endl;
    });
}

void testMazePrint() {
    int rows = 5;
    int cols = 5;
    Maze maze(rows, cols);
    std::cout << "Printing maze of size " << rows << "x" << cols << std::endl;
    maze.printMaze();
}

void testMazeString() {
    int rows = 4;
    int cols = 6;
    Maze maze(rows, cols);
    maze.setBox(0, 0, 'S');
    maze.setBox(0, 1, '#');
    maze.setBox(0, 2, '#');
    maze.setBox(3, 3, '#');
    maze.setBox(3, 4, '#');
    maze.setBox(3, 5, 'E');
    string mazeStr = "S##***\n";
          mazeStr += "******\n";
          mazeStr += "******\n";
          mazeStr += "***##E";
    if (maze.to_string() != mazeStr) {
        std::cout << "Maze to String failed " << CROSS_EMOJI << std::endl;
        return;
    }
    std::cout << "Maze to String successful " << CHECK_EMOJI << std::endl;
}

void testMazeSave() {
    int rows = 3;
    int cols = 5;
    Maze maze(rows, cols);
    maze.setBox(0, 0, 'S');
    maze.setBox(0, 1, '#');
    maze.setBox(0, 2, '#');
    maze.setBox(2, 3, '#');
    maze.setBox(2, 4, 'E');
    // ./saves/testMaze.txt
    maze.saveToFile("./saves/testMazeSave.txt");
    // Read the file and compare
    ifstream file("./saves/testMazeSave.txt");
    if (file.is_open()) {
        string line;
        int i = 0;
        while (getline(file, line)) {
            for (int j = 0; j < line.size(); j++) {
                if (line[j] != maze.getBox(i, j).getType()) {
                    std::cout << "Maze save failed " << CROSS_EMOJI << std::endl;
                    return;
                }
            }
            i++;
        }
        file.close();
    }
    std::cout << "Maze save successful " << CHECK_EMOJI << std::endl;
}

void testMazeLoad() {
    // Write to file
    int rows = 3;
    int cols = 5;
    // write to file
    ofstream file("./saves/testMazeLoad.txt");
    if (file.is_open()) {
        file << "S##**\n";
        file << "*****\n";
        file << "#*##E";
        file.close();
    }
    string mazestr = "S##**";
    mazestr += "*****";
    mazestr += "#*##E";
    // Load from file
    Maze maze(rows, cols);
    maze.loadFromFile("./saves/testMazeLoad.txt");
    // Compare
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if(maze.getBox(i, j).getType() != mazestr[i * cols + j]) {
                std::cout << "Maze load failed " << CROSS_EMOJI << std::endl;
                return;
            }
        }
    }
    std::cout << "Maze load successful " << CHECK_EMOJI << std::endl;
}
                
    

