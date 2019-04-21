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

private:
    Ui::MainWindow *ui;

    // LOAD FILES
    void loadFile();
    std::vector<Cell> ParseXML(std::string &file);

    // MODIFIER
    void createGrid(std::vector<Cell> cellVec);
    void createGrid(uint row, uint col);
    void refreshTable();
    void changeState(uint id);
    int modifyItem(QTableWidgetItem* item, int val);

    // VIEW
    void printGrid();

    // ADAPTER
    std::string gridToString();

    // PRIVATE VARS
    QString loaded_file; // currently loaded file
    uint row; // rows in puzzle
    uint col; // cols in puzzle
    uint cellSize; // size of cells on QTableWidget
    deque<Cell> undo_moves;
    deque<Cell> redo_moves;
    std::vector<std::vector<int> > grid; // puzzle grid

    // 0 is create
    // 1 is solve
    // 2 is view
    uint state;
};

bool isNumber(string s);

#endif // MAINWINDOW_H
