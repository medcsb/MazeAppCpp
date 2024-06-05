#include "headers/algorithm.hpp"

Algorithm::Algorithm(Maze& maze): maze(maze) {}

void Algorithm::setAlgo(std::string& algo){
    this->algo = algo;
}

std::vector<Coords> Algorithm::solveMaze(){
    if (algo == "DSF") {
        return DSF();
    } else if (algo == "BFS") {
        return BFS();
    } else if (algo == "AStar") {
        return AStar();
    } else if (algo == "Dijkstra") {
        return Dijkstra();
    } else {
        std::cerr << "Invalid algorithm" << std::endl;
        return std::vector<Coords>();
    }
}

void Algorithm::solveMazeStepByStep(){
    if (algo == "DSF") {
        DSFStep();
    } else if (algo == "BFS") {
        BFSStep();
    } else if (algo == "AStar") {
        AStarStep();
    } else if (algo == "Dijkstra") {
        DijkstraStep();
    } else {
        std::cerr << "Invalid algorithm" << std::endl;
    }
}

std::vector<Coords> Algorithm::DSF(){
    std::vector<Coords> path;
    std::stack<Coords> stack;
    std::vector<Coords> visited;
    std::map<Coords, std::vector<Coords>> parentChildMap;
    Coords start = maze.getStart();
    Coords end = maze.getEnd();
    visited.push_back(start);
    while(start != end){
        std::vector<Coords> neighbours = maze.getNeighboursCoords(start.x, start.y);
        for (Coords neighbour : neighbours){
            if ((!utils::contains(visited, neighbour)) && (!utils::contains(stack, neighbour))){
                stack.push(neighbour);
                parentChildMap[neighbour].push_back(start); 
        }
        start = stack.top();
        stack.pop();
        visited.push_back(start);
    }
    Coords current = end;
    while (current != maze.getStart()){
        path.push_back(current);
        current = parentChildMap[current][0];
    }
    return utils::flip(path);
}