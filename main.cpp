#include <iostream>
#include <vector>


struct Point {
    enum cellType {
        Wall=0, Corridor, Start, Finish
    };
    cellType type;
    int x, y;
};

typedef std::vector<std::vector<Point> > Maze;

void addWalls(Point p, std::vector<Point> &walls, Maze maze) {
    if (p.x > 0) {
        if (maze[p.x - 1][p.y].type == Point::Wall) {
            walls.push_back(maze[p.x - 1][p.y]);
        }
    }
    if (p.x < maze.size() - 1) {
        if (maze[p.x + 1][p.y].type == Point::Wall) {
            walls.push_back(maze[p.x + 1][p.y]);
        }
    }
    if (p.y > 0) {
        if (maze[p.x][p.y - 1].type == Point::Wall) {
            walls.push_back(maze[p.x][p.y - 1]);
        }
    }
    if (p.y < maze[0].size() - 1) {
        if (maze[p.x][p.y + 1].type == Point::Wall) {
            walls.push_back(maze[p.x][p.y + 1]);
        }
    }
}

bool onlyOneExit(Point p, Maze maze) {
    int exits = -1;
    if (p.x > 0) {
        if (maze[p.x - 1][p.y].type != Point::Wall) {
            if (++exits) return false;
        }
    }
    if (p.x < maze.size() - 1) {
        if (maze[p.x + 1][p.y].type != Point::Wall) {
            if (++exits) return false;
        }
    }
    if (p.y > 0) {
        if (maze[p.x][p.y - 1].type != Point::Wall) {
            if (++exits) return false;
        }
    }
    if (p.y < maze[0].size() - 1) {
        if (maze[p.x][p.y + 1].type != Point::Wall) {
            if (++exits) return false;
        }
    }
    return true;
}

void printMaze(Maze maze){
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[0].size(); j++) {
            switch(maze[i][j].type){
                case Point::Wall:
                    std::cout << "*";
                    break;
                case Point::Corridor:
                    std::cout << "o";
                    break;
                case Point::Start:
                    std::cout << "s";
                    break;
            }
        }
        std::cout << std::endl;
    }
    std::cout << "-------------" << std::endl;
}

void createMaze2D(int n) {
    Maze maze;
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

    maze[0][0].type = Point::Start;
    std::vector<Point> walls;
    addWalls(maze[0][0], walls, maze);

    while (!walls.empty()) {
        int r = rand() % walls.size();
        Point p = walls[r];
        if (onlyOneExit(p, maze)){
            maze[p.x][p.y].type = Point::Corridor;
            addWalls(p, walls, maze);
        }
        walls.erase(walls.begin() + r);
    }
    printMaze(maze);
};


int main(){
    int n;
    std::cin >> n;
    createMaze2D(n);

    return 0;
}