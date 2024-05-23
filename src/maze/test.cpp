#include "headers/test.hpp"

int main()
{
    Maze maze(5, 5);
    std::cout << "----------------" << std::endl;
    std::cout << maze.to_string();
    std::cout << "----------------" << std::endl;
    maze.saveToFile("./saves/maze.txt");
    Maze maze2(5, 5);
    maze2.loadFromFile("./saves/maze1.txt");
    std::cout << maze2.to_string() << std::endl;
    return 0;
}
