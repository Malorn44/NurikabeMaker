#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <QTableWidgetItem>
#include <QMainWindow>

#include "tinyxml2.h"

typedef unsigned int uint;

namespace Ui {
class MainWindow;
}

struct Cell {
    int value;
    int x;
    int y;
};

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

    void on_pushButton_clicked();

    void on_checkPuzzle_clicked();

private:
    Ui::MainWindow *ui;
    void loadFile();
    std::vector<Cell> ParseXML(std::string &file);
    void createGrid(std::vector<Cell> cellVec);
    void createGrid(uint row, uint col);
    void refreshTable();
    void changeState(uint id);
    void printGrid();
    std::string gridToString();

    QString loaded_file;
    uint row;
    uint col;
    uint cellSize;
    std::vector<std::vector<int> > grid;

    // 0 is create
    // 1 is solve
    // 2 is view
    uint state;
};

#endif // MAINWINDOW_H
