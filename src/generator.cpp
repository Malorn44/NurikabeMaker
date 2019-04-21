#include "generator.h"

// default constructor for Point, just initializes to 0
Point::Point() {
    r = 0;
    c = 0;
}

// constructs a Point using given row and col values
Point::Point(int row, int col) {
    r = row;
    c = col;
}

// equality operator for Point (if r and c is equal)
bool operator==(const Point &n1, const Point &n2) {
    return (n1.r == n2.r && n1.c == n2.c);
}

// constructor for generator, creates a grid of size row x col
Generator::Generator(int row, int col) {
    this->row = row;
    this->col = col;

    for (int i = 0; i < row; i++) {
        m_grid.push_back(vector<int>());
        for (int j = 0; j < col; j++) {
            m_grid[i].push_back(0);
        }
    }
}

// generates a puzzle using a maze algorithm with the Nurikabe puzzle rule of no 2x2
// blacks as a heuristic. Has the side-effect of tending to use certain shapes and creates
// too many 1s. Does not guarantee a puzzle with only one solution.
void Generator::generate() {
    // current point, set m_grid[curr.r][curr.c] to be black
    Point curr(rand() % row, rand() % col);
    m_grid[curr.r][curr.c] = -1;

    // push back the current point onto the stack
    stack.push_back(curr);

    // maze algorithm part (runs until stack is empty)
    while (!stack.empty()) {
        curr = stack[stack.size()-1];

        // gets a random, valid, child
        Point child = getRandomChild(curr.r, curr.c);
        // if there are no children we remove curr from stack and continue
        // OR there is a random chance we ignore the child found (this was an attempt to counterract
        // the shortcomings of the maze algorithm and it had moderate success so I left it in)
        // Sometimes it creates really bad puzzles, but it usually creates higher quality ones than it used to
        if (child.r == -1 || ((double)rand() / RAND_MAX) < 0.05) {
            stack.pop_back();
            continue;
        }

        m_grid[child.r][child.c] = -1;
        stack.push_back(child);
    }
}

// checks if the current point would be part of a 2x2 if it were to be made black
bool Generator::partOfSquare(int i, int j) {
    if (i+1 < row && j+1 < col) {
        if (m_grid[i+1][j] == -1 && m_grid[i+1][j+1] == -1 && m_grid[i][j+1] == -1) return true;
    }
    if (i+1 < row && j-1 >= 0) {
        if (m_grid[i+1][j] == -1 && m_grid[i+1][j-1] == -1 && m_grid[i][j-1] == -1) return true;
    }
    if (i-1 >= 0 && j+1 < col) {
        if (m_grid[i-1][j] == -1 && m_grid[i-1][j+1] == -1 && m_grid[i][j+1] == -1) return true;
    }
    if (i-1 >= 0 && j-1 >= 0) {
        if (m_grid[i-1][j] == -1 && m_grid[i-1][j-1] == -1 && m_grid[i][j-1] == -1) return true;
    }
    return false;
}

// returns a random, valid child (or a Point(-1,-1) if there are no children)
Point Generator::getRandomChild(int i, int j) {
    vector<Point> children;
    if (i+1 < row) {
        if (!partOfSquare(i+1,j) && m_grid[i+1][j] == 0) {
            children.push_back(Point(i+1,j));
        }
    }
    if (i-1 >= 0) {
        if (!partOfSquare(i-1,j) && m_grid[i-1][j] == 0) {
            children.push_back(Point(i-1,j));
        }
    }
    if (j+1 < col) {
        if (!partOfSquare(i,j+1) && m_grid[i][j+1] == 0) {
            children.push_back(Point(i,j+1));
        }
    }
    if (j-1 >= 0) {
        if (!partOfSquare(i,j-1) && m_grid[i][j-1] == 0) {
            children.push_back(Point(i,j-1));
        }
    }

    if (children.empty()) return Point(-1,-1);

    int r = rand() % children.size();
    return children[r];
}

// BFS on every "room" to find the number of cells in that room. Sets a random
// cell in that room to be the number of cells found.
void Generator::fillInNumbers() {

    // creates a vector of all the white tiles
    vector<Point> whites;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (m_grid[i][j] == 0) {
                whites.push_back(Point(i,j));
            }
        }
    }

    // while there are still white tiles
    while (!whites.empty()) {
        // create a queue and push back the last white, and remove it from whites
        queue<Point> q;
        q.push(whites[whites.size()-1]);
        whites.pop_back();

        // create a visited vector to store all the cells visited
        vector<Point> visited;
        visited.push_back(q.front());

        // calls BFS to search, populates visited vector
        BFS(m_grid, q, visited, 0);

        // sets random visited cell to be size of visited
        int randIndex = rand() % visited.size();
        m_grid[visited[randIndex].r][visited[randIndex].c] = visited.size();

        // removes all visited cells from whites
        for (int i = 0; i < visited.size(); i++) {
            for (int j = 0; j < whites.size(); j++) {
                if (visited[i] == whites[j]) {
                    whites.erase(whites.begin() + j);
                }
            }
        }
    }
}

// sets every cell in grid equaling val, to 0
void Generator::removeValue(int val) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (m_grid[i][j] == val) {
                m_grid[i][j] = 0;
            }
        }
    }
}

// returns a vector of all valid children (a child is valid if it equals val)
vector<Point> getValidChildren(const vector<vector<int> > &grid, const Point &p, int val) {
    vector<Point> children;
    int row = grid.size();
    int col = grid[0].size();
    int i = p.r;
    int j = p.c;
    if (i+1 < row) {
        if (grid[i+1][j] == val) {
            children.push_back(Point(i+1,j));
        }
    }
    if (i-1 >= 0) {
        if (grid[i-1][j] == val) {
            children.push_back(Point(i-1,j));
        }
    }
    if (j+1 < col) {
        if (grid[i][j+1] == val) {
            children.push_back(Point(i,j+1));
        }
    }
    if (j-1 >= 0) {
        if (grid[i][j-1] == val) {
            children.push_back(Point(i,j-1));
        }
    }
    return children;
}

// breadth first searches on first value in q, populates visited vector
void BFS(vector<vector<int> > &grid, queue<Point> &q, vector<Point> &visited, int val) {
    while (!q.empty()) {
        Point p = q.front();
        q.pop();

        // gets valid children
        vector<Point> children = getValidChildren(grid, p, val);

        // adds every valid child to q if it isn't in visited
        for (int i = 0; i < children.size(); i++) {
            if (std::find(visited.begin(), visited.end(), children[i]) == visited.end()) {
                q.push(children[i]);
                // push child back to visited if it wasn't in there
                visited.push_back(children[i]);
            }
        }
    }
}


