#include <iostream>
#include <QFileDialog>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nurikabe.h"
#include "newfile.h"

void printCell (const Cell& cell) {
    std::cout << "cell {value: " << cell.value << " x: " << cell.x << " y: " << cell.y << " }" << std::endl;
}

bool isNumber(string s) {
    if (s.size() == 0) return false;
    for (uint i = 0; i < s.length(); i++)
        if (isdigit(s[i]) == false)
            return false;
    return true;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusView->setStyleSheet("QLabel { background-color : green; color : white }");
    createDefaultGrid();

    // remove table headers
    ui->Board->horizontalHeader()->setVisible(false);
    ui->Board->verticalHeader()->setVisible(false);

    // table styling
    ui->Board->setFocusPolicy(Qt::NoFocus);
    ui->Board->setSelectionMode(QAbstractItemView::NoSelection);
//    ui->Board->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->Board->horizontalHeader()->setMinimumSectionSize(10);
    ui->Board->verticalHeader()->setMinimumSectionSize(10);
    ui->Board->setFont(QFont("Times",12));

    refreshTable();

//    connect( ui->board, &QTableWidget::itemEntered, this, &MainWindow::onItemClicked );
    connect( ui->Board, &QTableWidget::itemPressed, this, &MainWindow::onItemClicked );
    connect( ui->Board, &QTableWidget::itemChanged, this, &MainWindow::onNumEntered );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onItemClicked(QTableWidgetItem *item) {
    if (state == 0) {
//        ui->Board->setEditTriggers(QAbstractItemView::EditTriggers);
//        item->setBackground(Qt::white);
    } else if (state == 1) {

    }
}

void MainWindow::onNumEntered(QTableWidgetItem *item) {
    if (state != 0) return;
    if (isNumber(item->text().toStdString())) {
        uint textAsNum = stoul(item->text().toStdString());
        if (textAsNum != 0) {
            item->setBackground(Qt::white);
            grid[item->row()][item->column()] = stoul(item->text().toStdString());
            return;
        }
    }
    item->setBackground(Qt::lightGray);
    item->setText("");
    grid[item->row()][item->column()] = 0;
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
            selectedItem->setTextAlignment(Qt::AlignCenter);
            if (grid[i][j] == 0) {
                selectedItem->setBackground(Qt::lightGray);
            } else if (grid[i][j] > 0) {
                selectedItem->setBackground(Qt::white);
                selectedItem->setText(QString::number(grid[i][j]));
            } else if (grid[i][j] == -1) {
                selectedItem->setBackground(Qt::black);
            } else if (grid[i][j] == -2) {
                selectedItem->setBackground(Qt::white);
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

    size_t last = file.find_last_of("/");
    if (last != std::string::npos) file = file.substr(last+1);

    ui->console->setText(QString::fromStdString("Puzzle name: " + file + "\t Height: " +
                                                to_string(row) + "\t Width: " + to_string(col)));
    return cellVec;
}

void MainWindow::createDefaultGrid() {
    ui->console->setText("No file loaded...");
    ui->statusView->setText("CREATE");
    ui->statusView->setStyleSheet("QLabel { background-color : green; color : white }");
    state = 0;
    loaded_file = "";

    row = 15;
    col = 15;
    cellSize = 30;

    // initialize grid
    for (uint i = 0; i < row; i++) {
        grid.push_back(std::vector<int>());
        for (uint j = 0; j < col; j++) {
            grid[i].push_back(0);
        }
    }
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
    uint old_state = state;
    state = 1;
    std::string file = loaded_file.toStdString();
    std::vector<Cell> cellVec = ParseXML(file);
    if (cellVec.empty()) { // handles the case of no file found
        state = old_state;
        return;
    }
    createGrid(cellVec);
    refreshTable();
    ui->statusView->setText("SOLVE");
    ui->statusView->setStyleSheet("QLabel { background-color : blue; color : white }");
    ui->Board->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

std::string MainWindow::gridToString() {
    std::string output = "";
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (grid[i][j] <= 0) {
                output += " ";
            } else if (grid[i][j] > 0) {
                output += std::to_string(grid[i][j]);
            }
        }
        output += "\n";
    }
    return output;
}

void MainWindow::on_actionLoad_triggered()
{
    loaded_file = QFileDialog::getOpenFileName(
                this, tr("Open File"),
                "C:/Users/Max/Dropbox/Personal/Programming Projects/nurikabe_solver/puzzles",
                "All files (*.*);;XML File (*.xml)");
    loadFile();
}


void MainWindow::on_solvePuzzle_clicked()
{
    struct Puzzle {
        const char * name;
        int w;
        int h;
        const char * s;
    };

    state = 2;
    ui->Board->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->statusView->setText("VIEW");
    ui->statusView->setStyleSheet("QLabel { background-color : red; color : white }");
    ui->console->setText("Solving... this may take a moment.");

    Puzzle puzzle;
    puzzle.h = row;
    puzzle.w = col;

    std::string file = loaded_file.toStdString();
    size_t last = file.find_last_of("/");
    if (last != std::string::npos) file = file.substr(last+1);
    puzzle.name = file.c_str();

    std::string out = gridToString();
    std::cout << out << std::endl;
    puzzle.s = out.c_str();

    // converting to Puzzle object readable by the solver

    try {
        const auto start = steady_clock::now();

        Grid g(puzzle.w, puzzle.h, puzzle.s);

        while (g.solve() == Grid::KEEP_GOING) { }

        const auto finish = steady_clock::now();


        ofstream f(string("") + puzzle.name + string(".html"));

//        g.write(f, start, finish);
        grid = g.getFinal();
        refreshTable();

        const int k = g.known();
        const int cells = puzzle.w * puzzle.h;
        string status = (k-cells == 0) ? " solved.\t" : " not solved.\t";
        ui->console->setText(QString::fromStdString(string(puzzle.name) + status + to_string(k) + "/" +
                                                    to_string(cells) + " (" + to_string(k * 100.0 / cells) + "%)\t" +
                                                    format_time(start, finish)));
    } catch (const exception& e) {
        cerr << "EXCEPTION CAUGHT! \"" << e.what() << "\"" << std::endl;
        // TODO: Handle this exception
    } catch (...) {
        cerr << "UNKNOWN EXCEPTION CAUGHT!" << std::endl;
        // TODO: Handle this exception
    }
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionNew_triggered()
{
    NewFile newfile;
    newfile.setModal(true);
    newfile.exec();

    createDefaultGrid();
    refreshTable();

    ui->Board->setEditTriggers(QAbstractItemView::DoubleClicked);
}

void MainWindow::on_actionSave_triggered()
{
    using namespace tinyxml2;

//    XMLDeclaration* declaration = new XMLDeclaration("1.0");//Create DTD
//    TiXmlDocument* doc = new TiXmlDocument;
//    doc->LinkEndChild(declaration);

//    TiXmlElement* week = new TiXmlElement("week");
//    TiXmlElement* day = new TiXmlElement("day");
//    TiXmlElement* name = new TiXmlElement("name");
//    TiXmlElement* note = new TiXmlElement("note");
//    TiXmlElement* tl = new TiXmlElement("tl");
//    TiXmlElement* ti = new TiXmlElement("ti");
//    TiXmlText* dayName = new TiXmlText("");
//    TiXmlText* dayNote = new TiXmlText("");

    XMLDocument doc;

    XMLElement* legup = doc.NewElement("Legup");
    legup->SetAttribute("version","2.0.0");
    XMLElement* puzzle = doc.NewElement("puzzle");
    puzzle->SetAttribute("name","Nurikabe");
    XMLElement* board = doc.NewElement("board");
    board->SetAttribute("height",to_string(row).c_str());
    board->SetAttribute("width",to_string(col).c_str());
    XMLElement* cells = doc.NewElement("cells");
    vector<XMLElement*> all_cells;
    for (int i = row-1; i >= 0; i--) {
        for (int j = col-1; j >= 0; j--) {
            if (grid[i][j] > 0) {
                XMLElement* cell = doc.NewElement("cell");
                cell->SetAttribute("value",to_string(grid[i][j]).c_str());
                cell->SetAttribute("x",to_string(j).c_str());
                cell->SetAttribute("y",to_string(i).c_str());
                cells->InsertFirstChild(cell);
            }
        }
    }
    board->InsertFirstChild(cells);
    puzzle->InsertFirstChild(board);
    legup->InsertFirstChild(puzzle);
    doc.InsertFirstChild(legup);

    // creating the declaration header
    XMLDeclaration* declaration = doc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"");
    doc.InsertFirstChild(declaration);

    doc.SaveFile("C:/Users/Max/Dropbox/Personal/Programming Projects/nurikabe_solver/puzzles/new");
//    doc.FirstChildElement(XMLElement("Legup"));

//    const XMLElement* puzzle = doc.FirstChildElement("Legup")->FirstChildElement("puzzle");
//    const std::string puzzleName(puzzle->Attribute("name"));
//    const XMLElement* board = puzzle->FirstChildElement("board");
//    const std::string h(board->Attribute("height"));
//    const std::string w(board->Attribute("width"));
//    const XMLElement* cell = board->FirstChildElement("cells")->FirstChildElement("cell");
}
