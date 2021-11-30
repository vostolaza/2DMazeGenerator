#include <iostream>
#include <vector>
#include <time.h>

struct Point {
    enum cellType {
        Wall=0, Corridor, Start, Finish
    };
    cellType type;
    int x, y;
};

typedef std::vector<std::vector<Point> > Maze;

// Adds the surrounding walls to the vector
void addWalls(Point p, std::vector<Point> &walls, Maze maze) {
    // Left
    if (p.x > 0) {
        if (maze[p.x - 1][p.y].type == Point::Wall) {
            walls.push_back(maze[p.x - 1][p.y]);
        }
    }
    // Right
    if (p.x < maze.size() - 1) {
        if (maze[p.x + 1][p.y].type == Point::Wall) {
            walls.push_back(maze[p.x + 1][p.y]);
        }
    }
    // Up
    if (p.y > 0) {
        if (maze[p.x][p.y - 1].type == Point::Wall) {
            walls.push_back(maze[p.x][p.y - 1]);
        }
    }
    // Down
    if (p.y < maze[0].size() - 1) {
        if (maze[p.x][p.y + 1].type == Point::Wall) {
            walls.push_back(maze[p.x][p.y + 1]);
        }
    }
}

// Checks if there is only one possible exit from said point in order to avoid cycles
// so that there is only one way to reach the exit.
bool onlyOneExit(Point p, Maze maze) {
    int exits = -1;
    // Left
    if (p.x > 0) {
        if (maze[p.x - 1][p.y].type != Point::Wall) {
            if (++exits) return false;
        }
    }
    // Right
    if (p.x < maze.size() - 1) {
        if (maze[p.x + 1][p.y].type != Point::Wall) {
            if (++exits) return false;
        }
    }
    // Up
    if (p.y > 0) {
        if (maze[p.x][p.y - 1].type != Point::Wall) {
            if (++exits) return false;
        }
    }
    // Down
    if (p.y < maze[0].size() - 1) {
        if (maze[p.x][p.y + 1].type != Point::Wall) {
            if (++exits) return false;
        }
    }
    return true;
}

void printMaze(Maze maze){
    for (int i = 0; i < maze.size()+2; i++) std::cout << "*";
    std::cout << std::endl;
    for (int i = 0; i < maze.size(); i++) {
        std:: cout << "*";
        for (int j = 0; j < maze[0].size(); j++) {
            switch(maze[i][j].type){
                case Point::Wall:
                    std::cout << "*";
                    break;
                case Point::Corridor:
                    std::cout << "o";
                    break;
                case Point::Start:
                    std::cout << "A";
                    break;
                case Point::Finish:
                    std::cout << "B";
            }
        }
        std::cout << "*" << std::endl;
    }
    for (int i = 0; i < maze.size()+2; i++) std::cout << "*";
}

void createMaze2D(int n) {
    Maze maze;
    // Initializes the maze full of walls
    for (int i = 0; i < n; i++) {
        std::vector<Point> row;
        for (int j = 0; j < n; j++) {
            Point p;
            p.x = i;
            p.y = j;
            p.type = Point::Wall;
            row.push_back(p);
        }
        maze.push_back(row);
    }

    // Selects the starting point
    maze[0][0].type = Point::Start;
    std::vector<Point> walls;
    // Adds the surrounding walls to the vector
    addWalls(maze[0][0], walls, maze);

    // Variable that will become the finish point.
    Point lastPoint;

    // Selects a random wall that is connected to a corridor and if it only has one exit, it becomes a corridor.
    // The new corridor's walls are added to the walls vector.
    // The last corridor to be made becomes the finish point.
    while (!walls.empty()) {
        int r = rand() % walls.size();
        Point p = walls[r];
        if (onlyOneExit(p, maze)){
            maze[p.x][p.y].type = Point::Corridor;
            addWalls(p, walls, maze);
            lastPoint = p;
        }
        walls.erase(walls.begin() + r);
    }
    maze[lastPoint.x][lastPoint.y].type = Point::Finish;
    printMaze(maze);
};


int main(){
    int n;
    bool validInput = false;
    while (!validInput) {
        std::cout << "Enter the size of the maze: ";
        std::cin >> n;
        if (n > 3 && n%2 != 0) {
            validInput = true;
        }
        else {
            std::cout << "Invalid input. Please enter an odd number greater than 3." << std::endl;
        }
    }
    srand (time(NULL));
    createMaze2D(n-2);

    return 0;
}