#include "headers/test.hpp"

int main()
{
    // Set console output to UTF-8 on Windows
#ifdef _WIN32
    SET_CONSOLE_UTF8
#endif // _WIN32
    setlocale(LC_ALL, "en_US.UTF-8");
    // **************************************
    std::cout << "size of mazeBox: " << sizeof(MazeBox) << std::endl;
    // Tests
    testMazeCreation();
    // testMazePrint();
    timeTaken(testMazeString);
    timeTaken(testMazeSave);
    timeTaken(testMazeLoad);
    timeTaken(testGetNeighbours);
    //timeTaken(testRawBinarySave);
    return 0;
}

void testMazeCreation() {
    timeTaken([]() {
        unsigned short rows = 20000;
        unsigned short cols = 30000;
        Maze maze = Maze(rows, cols);
        if (maze.getHeight() != rows || maze.getWidth() != cols) {
            std::cout << "Maze creation failed " << CROSS_EMOJI << std::endl;
            return;
        }
        //std::vector<std::vector<MazeBox>> boxes = maze.getBoxes();
        /*
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (boxes[i][j].getType() != '*') {
                    std::cout << "Wrong type for box (" << i << ", " << j << ") " << CROSS_EMOJI << std::endl;
                    return;
                }
            }
        }
        */
        std::cout << "Empty maze created successfully " << CHECK_EMOJI << std::endl;
    });
    return;
}

void testMazePrint() {
    unsigned short rows = 5;
    unsigned short cols = 5;
    Maze maze(rows, cols);
    std::cout << "Printing maze of size " << rows << "x" << cols << std::endl;
    maze.printMaze();
    return;
}

void testMazeString() {
    unsigned short rows = 4;
    unsigned short cols = 6;
    Maze maze(rows, cols);
    maze.setBox(0, 0, 'S');
    maze.setBox(0, 1, '#');
    maze.setBox(0, 2, '#');
    maze.setBox(3, 3, '#');
    maze.setBox(3, 4, '#');
    maze.setBox(3, 5, 'E');
    std::string mazeStr = "S##***\n";
          mazeStr += "******\n";
          mazeStr += "******\n";
          mazeStr += "***##E";
    if (maze.to_string() != mazeStr) {
        std::cout << "Maze to String failed " << CROSS_EMOJI << std::endl;
        return;
    }
    std::cout << "Maze to String successful " << CHECK_EMOJI << std::endl;
    return;
}

void testMazeSave() {
    unsigned short rows = 3;
    unsigned short cols = 5;
    Maze maze(rows, cols);
    maze.setBox(0, 0, 'S');
    maze.setBox(0, 1, '#');
    maze.setBox(0, 2, '#');
    maze.setBox(2, 3, '#');
    maze.setBox(2, 4, 'E');
    // ./saves/testMaze.txt
    maze.saveToFile("./saves/testMazeSave.txt");
    // Read the file and compare
    std::ifstream file("./saves/testMazeSave.txt");
    if (file.is_open()) {
        std::string line;
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
    return;
}

void testMazeLoad() {
    unsigned short rows = 3;
    unsigned short cols = 5;
    std::ofstream file("./saves/testMazeLoad.txt");
    if (file.is_open()) {
        file << "S##**\n";
        file << "*****\n";
        file << "#*##E";
        file.close();
    }
    std::string mazestr = "S##**";
    mazestr += "*****";
    mazestr += "#*##E";
    // Load from file
    Maze maze = Maze();
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
    return;
}

void testGetNeighbours() {
    unsigned short rows = 3;
    unsigned short cols = 4;
    Maze maze(rows, cols);
    std::vector<Coords> neighbours1 = maze.getNeighboursCoords(0, 0);
    std::vector<Coords> expected1 = {Coords{0, 1}, Coords{1, 0}};
    std::vector<Coords> neighbours2 = maze.getNeighboursCoords(2, 3);;
    std::vector<Coords> expected2 = {Coords{2, 2}, Coords{1, 3}};
    std::vector<Coords> neighbours3 = maze.getNeighboursCoords(1, 1);
    std::vector<Coords> expected3 = {Coords{1, 0}, Coords{0, 1}, Coords{1, 2}, Coords{2, 1}};
    std::vector<Coords> neighbours4 = maze.getNeighboursCoords(0, 2);
    std::vector<Coords> expected4 = {Coords{0, 1}, Coords{0, 3}, Coords{1, 2}};
    if (neighbours1 != expected1) {
        std::cout << "get neighbours failed " << CROSS_EMOJI << std::endl;
        std::cout << "on edge case (0, 0)" << std::endl;
        return;
    }
    if (neighbours2 != expected2) {
        std::cout << "get neighbours failed " << CROSS_EMOJI << std::endl;
        std::cout << "on edge case (2, 3)" << std::endl;
        return;
    }
    if (neighbours3 != expected3) {
        std::cout << "get neighbours failed " << CROSS_EMOJI << std::endl;
        std::cout << "on middle case (1, 1)" << std::endl;
        return;
    }
    if (neighbours4 != expected4) {
        std::cout << "get neighbours failed " << CROSS_EMOJI << std::endl;
        std::cout << "on middle case (0, 2)" << std::endl;
        return;
    }
    std::cout << "get neighbours successful " << CHECK_EMOJI << std::endl;
    return;
}

void testRawBinarySave() {
    unsigned short rows = 3820023;
    unsigned short cols = 123423;
    Maze maze(rows, cols);
    maze.setBox(0, 0, 'S');
    maze.setBox(0, 1, '#');
    maze.setBox(0, 2, '#');
    maze.setBox(3, 2, 'E');
    maze.saveRawBinary("./savesRaw/testRawBinarySave.bin");
    // Read the file and compare
    Maze maze2 = Maze();
    maze2.loadRawBinary("./savesRaw/testRawBinarySave.bin");
    return;
}
