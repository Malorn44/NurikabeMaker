#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
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

private:
    Ui::MainWindow *ui;
    void loadFile();
    std::vector<Cell> ParseXML(std::string &file);

    QString loaded_file;
    uint row;
    uint col;
    std::vector<std::vector<int> > grid;
};

#endif // MAINWINDOW_H
