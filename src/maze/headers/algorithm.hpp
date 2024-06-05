#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <stack>
#include <algorithm>
#include <map>
#include "maze.hpp"
#include "utils.hpp"

class Algorithm{
public:
    Algorithm(Maze& maze);
    void setAlgo(std::string& algo);
    std::vector<Coords> solveMaze();
    void solveMazeStepByStep();
    // Algorithms
    std::vector<Coords> DSF();
    std::vector<Coords> BFS();
    std::vector<Coords> AStar();
    std::vector<Coords> Dijkstra();
    // Step by step
    void DSFStep();
    void BFSStep();
    void AStarStep();
    void DijkstraStep();
private:
    Maze& maze;
    std::string algo;
    std::vector<std::vector<MazeBox>> step; // stores the current step of the algorithm
};

#endif // ALGORITHMS_HPP