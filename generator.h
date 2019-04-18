#ifndef GENERATOR_H
#define GENERATOR_H

#include <iostream>
#include <vector>
#include <time.h>
#include <queue>
#include <algorithm>

using namespace std;

struct Point {
    Point();
    Point(int row, int col);
    int r;
    int c;
};

class Generator
{
public:
    Generator(int row, int col);
    void generate();
    void fillInNumbers();
    void removeValue(int val);
    vector<vector<int> > getGrid() { return m_grid; }

private:
    int row;
    int col;

    vector<vector<int> > m_grid;
    vector<Point> stack;
    Point current();

    bool partOfSquare(int i, int j);
    Point getRandomChild(int i, int j);
    vector<Point> getValidChildren(const Point &p) const;
};

#endif // GENERATOR_H
