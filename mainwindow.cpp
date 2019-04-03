#include <iostream>
#include <QFileDialog>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

void printCell (const Cell& cell) {
    std::cout << "cell {value: " << cell.value << " x: " << cell.x << " y: " << cell.y << " }" << std::endl;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loaded_file = "";

    row = 10;
    col = 10;
    cellSize = 30;

    // initialize grid
    for (uint i = 0; i < row; i++) {
        grid.push_back(std::vector<int>());
        for (uint j = 0; j < col; j++) {
            grid[i].push_back(0);
        }
    }

    // remove table headers
    ui->Board->horizontalHeader()->setVisible(false);
    ui->Board->verticalHeader()->setVisible(false);

    // table styling
    ui->Board->setFocusPolicy(Qt::NoFocus);
    ui->Board->setSelectionMode(QAbstractItemView::NoSelection);
    ui->Board->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->Board->horizontalHeader()->setMinimumSectionSize(10);
    ui->Board->verticalHeader()->setMinimumSectionSize(10);
    ui->Board->setFont(QFont("Times",12));

    refreshTable();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshTable() {
    // set table row and col count
    ui->Board->setRowCount(row);
    ui->Board->setColumnCount(col);

    // set fixed column and row width
    for (uint i = 0; i < row; i++)
        ui->Board->setRowHeight(i, cellSize);
    for (uint i = 0; i < col; i++)
        ui->Board->setColumnWidth(i, cellSize);

    // populate with items
    for (uint i = 0; i < row; i++) {
        for (uint j = 0; j < col; j++) {
            ui->Board->setItem(i, j, new QTableWidgetItem);
            QTableWidgetItem* selectedItem = ui->Board->item(i, j);
            if (grid[i][j] == 0) {
                selectedItem->setBackground(Qt::lightGray);
            } else if (grid[i][j] > 0) {
                selectedItem->setBackground(Qt::white);
                selectedItem->setText(QString::number(grid[i][j]));
                selectedItem->setTextAlignment(Qt::AlignCenter);
            }
        }
    }

}

std::vector<Cell> MainWindow::ParseXML(std::string &file) {
    using namespace tinyxml2;

    XMLDocument doc;
    bool invalidFile = doc.LoadFile(file.c_str());

    // If the file couldn't be loaded we print an error message.
    if (invalidFile) {
        std::cerr << "Error! File not found." << endl;
        return std::vector<Cell>();
    }

    const XMLElement* puzzle = doc.FirstChildElement("Legup")->FirstChildElement("puzzle");
    const std::string puzzleName(puzzle->Attribute("name"));
    const XMLElement* board = puzzle->FirstChildElement("board");
    const std::string h(board->Attribute("height"));
    const std::string w(board->Attribute("width"));
    const XMLElement* cell = board->FirstChildElement("cells")->FirstChildElement("cell");

    std::vector<Cell> cellVec;

    // if the puzzleName is not Nurikabe then we have an incorrect puzzle.
    if (puzzleName != "Nurikabe") {
        std::cerr << "Invalid puzzle file! This program only acceps Nurikabe puzzles." << endl;
        return cellVec;
    }

    row = std::stoul(h);
    col = std::stoul(w);

    while (cell != nullptr) {
        Cell c;
        c.value = std::stoi(cell->Attribute("value"));
        c.x = std::stoi(cell->Attribute("x"));
        c.y = std::stoi(cell->Attribute("y"));
        cellVec.push_back(c);

        cell = cell->NextSiblingElement("cell");
    }

//    std::cout << "Puzzle read!" << std::endl;
//    std::cout << "Puzzle name: " << puzzleName << std::endl;
//    std::cout << "Board height: " << height << " width: " << width << std::endl;
//    std::cout << "Cells: " << std::endl;
//    for (const Cell& c : cellVec) {
//        printCell(c);
//    }

    return cellVec;
}

void MainWindow::createGrid(std::vector<Cell> cellVec) {
    grid.clear();
    for (uint i = 0; i < row; i++) {
        grid.push_back(std::vector<int>());
        for (uint j = 0; j < col; j++) {
            grid[i].push_back(0);
        }
    }
    for (Cell c : cellVec) {
        grid[c.y][c.x] = c.value;
    }
}

void MainWindow::loadFile() {
    std::string file = loaded_file.toStdString();
    std::vector<Cell> cellVec = ParseXML(file);
    createGrid(cellVec);
    refreshTable();
}

void MainWindow::on_actionLoad_triggered()
{
    loaded_file = QFileDialog::getOpenFileName(
                this, tr("Open File"),
                "C:/Users/Max/Dropbox/Personal/Programming Projects/nurikabe_solver/puzzles",
                "All files (*.*);;XML File (*.xml)");
    loadFile();
}
