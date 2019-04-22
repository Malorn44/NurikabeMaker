#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <vector>
#include <deque>
#include <QTableWidgetItem>
#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

#include "tinyxml2/tinyxml2.h"
#include "nurikabe/nurikabe.h"
#include "newfile.h"
#include "generator.h"

typedef unsigned int uint;

namespace Ui {
class MainWindow;
}

/* Stores information about a single cell
 * Used for undo/redo function and for the auto-solver
 */
struct Cell {
    Cell(int x, int y, int value);
    int value;
    int x;
    int y;
};

// State storage
struct State {
    State() : undo(deque<Cell>()), redo(deque<Cell>()), grid(vector<vector<int>>()) {}
    State(deque<Cell> undo, deque<Cell> redo, vector<vector<int> > grid);
    deque<Cell> undo;
    deque<Cell> redo;
    vector<vector<int> > grid;
};

/* MainWindow class for the program, handles most of the display tasks
 * and calculations for the puzzle grid representation
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionLoad_triggered();

    void on_solvePuzzle_clicked();

    void on_actionExit_triggered();

    void onItemClicked(QTableWidgetItem *item);

    void onNumEntered(QTableWidgetItem *item);

    void on_actionNew_triggered();

    void on_actionSave_triggered();

    void on_generatePuzzle_clicked();

    void on_actionCreate_triggered();

    void on_actionSolve_triggered();

    void on_actionView_triggered();

    void on_checkPuzzle_clicked();

    void on_undoMove_clicked();

    void on_redoMove_clicked();

    void on_saveState_1_triggered();

    void on_saveState_2_triggered();

    void on_saveState_3_triggered();

    void on_loadState_1_triggered();

    void on_loadState_2_triggered();

    void on_loadState_3_triggered();

private:
    Ui::MainWindow *ui;

    // LOAD FILES
    void loadFile();
    std::vector<Cell> ParseXML(std::string &file);

    // MODIFIER
    void createGrid(std::vector<Cell> cellVec);
    void createGrid(uint row, uint col);
    void refreshTable();
    void changeMode(uint id);
    void saveState(uint id);
    void loadState(uint id);
    int modifyItem(QTableWidgetItem* item, int val);

    // VIEW
    void printGrid();

    // ADAPTER
    std::string gridToString();

    // MEMBER VARS
    QString loaded_file; // currently loaded file
    uint row; // rows in puzzle
    uint col; // cols in puzzle
    uint cellSize; // size of cells on QTableWidget
    deque<Cell> undo_moves;
    deque<Cell> redo_moves;
    State states[3]; // stores 3 states
    std::vector<std::vector<int> > grid; // puzzle grid

    // 0 is create
    // 1 is solve
    // 2 is view
    uint mode;
};

bool isNumber(string s);

#endif // MAINWINDOW_H
