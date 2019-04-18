#include "generator.h"

Point::Point() {
    r = 0;
    c = 0;
}

Point::Point(int row, int col) {
    r = row;
    c = col;
}

bool operator==(const Point &n1, const Point &n2) {
    return (n1.r == n2.r && n1.c == n2.c);
}

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

//void Generator::draw() {
//    for (int i = 0; i < row; i++) {
//        for (int j = 0; j < col; j++) {
//            if (m_grid[i][j] == -1) {
//                cout << "# ";
//            } else {
//                cout << ". ";
//            }
//        }
//        cout << endl;
//    }
//    cout << endl;
//}

void Generator::generate() {
    int rr = rand() % row;
    int cc = rand() % col;
    Point curr(rr, cc);
    m_grid[curr.r][curr.c] = -1;

    cout << curr.r << " " << curr.c << endl;

    stack.push_back(curr);

    while (!stack.empty()) {
        curr = stack[stack.size()-1];
//        draw();
        Point child = getRandomChild(curr.r, curr.c);
        if (child.r == -1) {
            stack.pop_back();
            continue;
        }

        cout << child.r << " " << child.c << endl;
        m_grid[child.r][child.c] = -1;
        stack.push_back(child);
    }
}

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

void Generator::fillInNumbers() {

    vector<Point> whites;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (m_grid[i][j] == 0) {
                whites.push_back(Point(i,j));
            }
        }
    }

    while (!whites.empty()) {
        queue<Point> q;
        q.push(whites[whites.size()-1]);
        whites.pop_back();

        vector<Point> visited;
        visited.push_back(q.front());

        while (!q.empty()) {
            Point p = q.front();
            q.pop();

            vector<Point> children = getValidChildren(p);

            for (int i = 0; i < children.size(); i++) {
                if (std::find(visited.begin(), visited.end(), children[i]) == visited.end()) {
                    q.push(children[i]);
                    visited.push_back(children[i]);
                }
            }
        }

        int randIndex = rand() % visited.size();
        m_grid[visited[randIndex].r][visited[randIndex].c] = visited.size();

        for (int i = 0; i < visited.size(); i++) {
            for (int j = 0; j < whites.size(); j++) {
                if (visited[i] == whites[j]) {
                    whites.erase(whites.begin() + j);
                }
            }
        }
    }
}

vector<Point> Generator::getValidChildren(const Point &p) const {
    vector<Point> children;
    int i = p.r;
    int j = p.c;
    if (i+1 < row) {
        if (m_grid[i+1][j] >= 0) {
            children.push_back(Point(i+1,j));
        }
    }
    if (i-1 >= 0) {
        if (m_grid[i-1][j] >= 0) {
            children.push_back(Point(i-1,j));
        }
    }
    if (j+1 < col) {
        if (m_grid[i][j+1] >= 0) {
            children.push_back(Point(i,j+1));
        }
    }
    if (j-1 >= 0) {
        if (m_grid[i][j-1] >= 0) {
            children.push_back(Point(i,j-1));
        }
    }
    return children;
}

void Generator::removeValue(int val) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (m_grid[i][j] == val) {
                m_grid[i][j] = 0;
            }
        }
    }
}


