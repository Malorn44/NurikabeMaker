#include "mainwindow.h"
#include "ui_mainwindow.h"

/* Constructs a new Cell struct
 * @param x is the x coordinate of the cell
 * @param y is the y coordinate of the cell
 * @param value is the value of the cell (-2, -1, 0 or Natural Number)
 */
Cell::Cell(int x, int y, int value) {
    this->x = x;
    this->y = y;
    this->value = value;
}

/* Constructs a new State struct
 * @param undo is an undo queue
 * @param redo is a redo queue
 * @param grid is a puzzle grid
 */
State::State(deque<Cell> undo, deque<Cell> redo, vector<vector<int> > grid) {
    this->undo = undo;
    this->redo = redo;
    this->grid = grid;
}

/* @param s is the string being tested
 * @returns true if s is a number, false otherwise
 */
bool isNumber(string s) {
    if (s.size() == 0) return false;
    for (uint i = 0; i < s.length(); i++)
        if (isdigit(s[i]) == false)
            return false;
    return true;
}

// constructor for MainWindow. Sets defaults
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->console->setText("No file loaded...");

    for (int i = 0; i < 3; i++) {
        states[i] = State();
    }

    // create default 10x10 blank puzzle grid
    createGrid(10, 10);
    changeMode(0);

    // remove table headers
    ui->Board->horizontalHeader()->setVisible(false);
    ui->Board->verticalHeader()->setVisible(false);

    // table styling
    ui->Board->setFocusPolicy(Qt::NoFocus);
    ui->Board->setSelectionMode(QAbstractItemView::NoSelection);
    ui->Board->horizontalHeader()->setMinimumSectionSize(10);
    ui->Board->verticalHeader()->setMinimumSectionSize(10);
    ui->Board->setFont(QFont("Times",12));

    refreshTable();

    // connecting signals to slots (for manipulating the QTableWidget)
    connect( ui->Board, &QTableWidget::itemClicked, this, &MainWindow::onItemClicked );
    connect( ui->Board, &QTableWidget::itemChanged, this, &MainWindow::onNumEntered );
}

// destructor for MainWindow
MainWindow::~MainWindow()
{
    delete ui;
}

/* Initializes a new grid based on a row and col input
 * @param newRow is the new size of row
 * @param newCol is the new size of col
 * @modifies grid, loaded_file
 * @effects initializes a grid of size newRow x newCol and resets loaded_file
 */
void MainWindow::createGrid(uint newRow, uint newCol) {
    loaded_file = "";

    row = newRow;
    col = newCol;
    cellSize = 30;

    // initialize grid
    for (uint i = 0; i < row; i++) {
        grid.push_back(std::vector<int>());
        for (uint j = 0; j < col; j++) {
            grid[i].push_back(0);
        }
    }
}

/* Replaces the grid with a new one w/ same rows and cols
 * @param cellVec values that certain cells need to be
 * @modifies grid
 * @effects sets a row x col grid to 0 for every cell, except for those
 * specified in cellVec
 */
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

// Refreshes the QTableWidget with new information stored in member variables
void MainWindow::refreshTable() {
    // reset undo, redo queues
    undo_moves.clear();
    redo_moves.clear();
    ui->undoMove->setEnabled(false);
    ui->redoMove->setEnabled(false);

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
            } else if (grid[i][j] <= -2) {
                selectedItem->setBackground(Qt::white);
            }
        }
    }
}

/* @param id is the mode to be changed to (0, 1, 2)
 * Modifies edit triggers for QTableView based on mode, also enables the undo button for
 * mode 1 (if undo_moves/redo_moves not empty) and disables it otherwise
 */
void MainWindow::changeMode(uint id) {
    ui->undoMove->setEnabled(false);
    ui->redoMove->setEnabled(false);
    if (id == 0) {
        mode = 0;
        ui->Board->setEditTriggers(QAbstractItemView::DoubleClicked);
        ui->statusView->setText("CREATE");
        ui->statusView->setStyleSheet("QLabel { background-color : green; color : white }");
    } else if (id == 1) {
        mode = 1;
        ui->Board->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->statusView->setText("SOLVE");
        ui->statusView->setStyleSheet("QLabel { background-color : blue; color : white }");
        if (!undo_moves.empty()) ui->undoMove->setEnabled(true);
        if (!redo_moves.empty()) ui->redoMove->setEnabled(true);
    } else if (id == 2) {
        mode = 2;
        ui->Board->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->statusView->setText("VIEW");
        ui->statusView->setStyleSheet("QLabel { background-color : red; color : white }");
    } else {
        cerr << "ERROR: Invalid mode" << endl;
    }
}

// parses an XML file using tinyxml2
// @param file is the xml file to be parsed
// @returns a Cell vector for use by createGrid
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
        cellVec.emplace_back(std::stoi(cell->Attribute("x")),
                             std::stoi(cell->Attribute("y")),
                             std::stoi(cell->Attribute("value")));
        cell = cell->NextSiblingElement("cell");
    }

    size_t last = file.find_last_of("/");
    if (last != std::string::npos) file = file.substr(last+1);

    ui->console->setText(QString::fromStdString("Puzzle name: " + file + "\t Height: " +
                                                to_string(row) + "\t Width: " + to_string(col)));
    return cellVec;
}

// updates the grid using the createGrid function, modifies the current mode
// and calls ParseXML to populate a Cell vector (cellVec)
void MainWindow::loadFile() {
    uint old_mode = mode;
    mode = 1;
    std::string file = loaded_file.toStdString();
    std::vector<Cell> cellVec = ParseXML(file);
    if (cellVec.empty()) { // handles the case of no file found
        mode = old_mode;
        return;
    }
    createGrid(cellVec);
    refreshTable();
    changeMode(1);
}

// converts a grid vector into a string for use by the auto-solver
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

// Handles loading of a state
void MainWindow::saveState(uint id) {
    if (mode != 1) {
        QMessageBox::warning(
                    this,
                    tr("Save State"),
                    tr("Must be in \"Solve\" mode to save state"));
        return;
    }
    if (!states[id].grid.empty()) {\
        QMessageBox::StandardButton reply = QMessageBox::question(
                    this,
                    tr("Save State"),
                    tr(("Saved state already exists with grid of size " +
                        to_string(states[id].grid.size()) + "x" +
                        to_string(states[id].grid[0].size()) +
                        "\nOverwrite state?").c_str()),
                        QMessageBox::Yes|QMessageBox::No);
        if(reply == QMessageBox::No) {
            return;
        }
    }
    states[id] = State(undo_moves,
                       redo_moves,
                       grid);

    if (id == 0) {
        ui->loadState_1->setIcon(QIcon(":/icon/assets/valid.svg"));
        ui->loadState_1->setEnabled(true);
    } else if (id == 1) {
        ui->loadState_2->setIcon(QIcon(":/icon/assets/valid.svg"));
        ui->loadState_2->setEnabled(true);
    } else if (id == 2) {
        ui->loadState_2->setIcon(QIcon(":/icon/assets/valid.svg"));
        ui->loadState_2->setEnabled(true);
    }
}

// Handles saving of a state
void MainWindow::loadState(uint id) {
    if (mode != 1) {
        QMessageBox::warning(
                    this,
                    tr("Load State"),
                    tr("Must be in \"Solve\" mode to load state"));
        return;
    }

    grid = states[id].grid;
    refreshTable();

    // need to do this after since refreshTable clears undo/redo
    undo_moves = states[id].undo;
    redo_moves = states[id].redo;

    changeMode(1);
}

/*** SLOTS ***/

// catches an itemClicked signal
// changes the color of a cell if mode is 1
void MainWindow::onItemClicked(QTableWidgetItem *item) {
    if (undo_moves.size() > 99) undo_moves.pop_back();
    if (mode == 1) {
        uint iRow = item->row();
        uint iCol = item->column();
        if (grid[iRow][iCol] > 0) return;
        if (item->backgroundColor() == Qt::lightGray) {
            item->setBackground(Qt::black);
            grid[iRow][iCol] = -1;
            undo_moves.emplace_front(iCol,iRow,0);
        } else if (item->backgroundColor() == Qt::black) {
            item->setBackground(Qt::white);
            grid[iRow][iCol] = -2;
            undo_moves.emplace_front(iCol,iRow,-1);
        } else if (item->backgroundColor() == Qt::white) {
            item->setBackground(Qt::lightGray);
            grid[iRow][iCol] = 0;
            undo_moves.emplace_front(iCol,iRow,-2);
        }
    }
    if (!undo_moves.empty()) {
        ui->undoMove->setEnabled(true);
    }
    if (!redo_moves.empty()) {
        redo_moves.clear();
        ui->redoMove->setEnabled(false);
    }
}

// catches an itemChanged signal
// updates the text of a cell if user enters a valid number and if mode is 0
void MainWindow::onNumEntered(QTableWidgetItem *item) {
    if (mode != 0) return;
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

// opens the QFileDialog to get a file name to load in
// calls loadFile which loads in whatever loaded_file is
void MainWindow::on_actionLoad_triggered()
{
    loaded_file = QFileDialog::getOpenFileName(
                this, tr("Open File"),
                "C:/Users/Max/Dropbox/Personal/Programming Projects/nurikabe_solver/puzzles",
                "All files (*.*);;XML File (*.xml)");
    loadFile();
}

// calls the autosolver
void MainWindow::on_solvePuzzle_clicked()
{
    // struct for input into the auto-solver
    struct Puzzle {
        const char * name;
        int w;
        int h;
        const char * s;
    };

    // updates the mode to "view"
    changeMode(2);
    ui->console->setText("Solving... this may take a moment.");

    // creates Puzzle
    Puzzle puzzle;
    puzzle.h = row;
    puzzle.w = col;

    std::string file = loaded_file.toStdString();
    size_t last = file.find_last_of("/");
    if (last != std::string::npos) file = file.substr(last+1);
    puzzle.name = file.c_str();

    // converting to Puzzle object readable by the solver
    std::string out = gridToString();
    std::cout << out << std::endl;
    puzzle.s = out.c_str();

    try {
        const auto start = steady_clock::now();
        Grid g(puzzle.w, puzzle.h, puzzle.s);
        while (g.solve() == Grid::KEEP_GOING) { }
        const auto finish = steady_clock::now();

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

// opens newFile dialog for user to type in rows and columns of
// new puzzle files. Handles any potentialy errors from the dialog
void MainWindow::on_actionNew_triggered()
{
    NewFile newfile;
    newfile.setModal(true);
    if (newfile.exec() == QDialog::Accepted) {
        if (newfile.getRow() == -1 || newfile.getCol() == -1) return;
        changeMode(0);
        createGrid(newfile.getRow(),newfile.getCol());
        refreshTable();
    }
}

// uses tinyxml2 to create a new xml file and then prompts the user to
// save it to a location on their computer
void MainWindow::on_actionSave_triggered()
{
    using namespace tinyxml2;

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

    QString saveFile = QFileDialog::getSaveFileName(
                this, tr("Open File"),
                "C:/Users/Max/Dropbox/Personal/Programming Projects/nurikabe_solver/puzzles",
                "All files (*.*);;XML File (*.xml)");
    cout << saveFile.toStdString() << endl;
    doc.SaveFile(saveFile.toStdString().c_str());
}

// checks if a puzzle is solved or not. There are 4 checks
// that it needs to pass in order to be declared as solved.
void MainWindow::on_checkPuzzle_clicked()
{
    QMessageBox check;
    check.setWindowTitle("Solve Checker");

    // create temporary grid for checking
    vector<vector<int> > temp_grid;

    // populate search spaces
    vector<Point> white_search;
    vector<Point> black_search;
    for (int i = 0; i < row; i++) {
        temp_grid.push_back(vector<int>());
        for (int j = 0; j < col; j++) {
            if (grid[i][j] <= -2) {
                temp_grid[i].push_back(0);
            } else {
                temp_grid[i].push_back(grid[i][j]);
            }
            if (grid[i][j] > 0) {
                white_search.push_back(Point(i,j));
            }
            if (grid[i][j] == -1) {
                black_search.push_back(Point(i,j));
            }
        }
    }

    // BFS call for checking if whites are satisfied
    while (!white_search.empty()) {
        queue<Point> q;
        q.push(white_search[white_search.size()-1]);
        int val = grid[q.front().r][q.front().c];
        white_search.pop_back();

        vector<Point> visited;
        visited.push_back(q.front());

        BFS(temp_grid, q, visited, 0);

        if (val != visited.size()) {
            check.setText("ERROR: Rooms are the wrong size");
            check.exec();
            return;
        }

        for (int i = 0; i < visited.size(); i++) {
            if (temp_grid[visited[i].r][visited[i].c] != 0) continue;
            temp_grid[visited[i].r][visited[i].c] = -2;
        }
    }

    // checks to make sure there are un-filled chunks
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (temp_grid[i][j] == 0) {
                check.setText("ERROR: Rooms without a number");
                check.exec();
                return;
            }
        }
    }

    // check if all blacks are connected
    vector<Point> visited;
    queue<Point> q;
    q.push(black_search[0]);
    visited.push_back(q.front());
    BFS(temp_grid, q, visited, -1);
    if (visited.size() != black_search.size()) {
        check.setText("ERROR: Walls aren't connected");
        check.exec();
        return;
    }

    // check for 2x2 blacks
    for (int i = 0; i < row-1; i++) {
        for (int j = 0; j < col-1; j++) {
            if (temp_grid[i][j] == -1 && temp_grid[i+1][j] == -1 &&
                    temp_grid[i+1][j+1] == -1 && temp_grid[i][j+1] == -1) {
                check.setText("ERROR: Can't have 2x2 walls");
                check.exec();
                return;
            }
        }
    }

    // if solved, update table
    // change mode to VIEW
    grid = temp_grid;
    refreshTable();
    changeMode(2);

    check.setText("Congratulations! You've solved the puzzle.");
    check.exec();
}

// generates a puzzle using Generator
void MainWindow::on_generatePuzzle_clicked()
{
    changeMode(1);

    // generates a random number seed for use by Generator
    srand(time(NULL));

    Generator g(row, col);
    g.generate();       // generates the puzzle
    g.fillInNumbers();  // fills in sizes of rooms
    g.removeValue(-1);  // removes walls (solution)
    grid = g.getGrid();

    refreshTable();
}

// MODE CHANGE //
void MainWindow::on_actionCreate_triggered()
{
    changeMode(0);
}
void MainWindow::on_actionSolve_triggered()
{
    changeMode(1);
}
void MainWindow::on_actionView_triggered()
{
    changeMode(2);
}
// MODE CHANGE //

// SAVE STATE //
void MainWindow::on_saveState_1_triggered()
{
    saveState(0);
}

void MainWindow::on_saveState_2_triggered()
{
    saveState(1);
}

void MainWindow::on_saveState_3_triggered()
{
    saveState(2);
}
// SAVE STATE //

// LOAD STATE //
void MainWindow::on_loadState_1_triggered()
{
    loadState(0);
}

void MainWindow::on_loadState_2_triggered()
{
    loadState(1);
}

void MainWindow::on_loadState_3_triggered()
{
    loadState(2);
}
// LOAD STATE//

// undoes the last move
void MainWindow::on_undoMove_clicked()
{
    Cell c = undo_moves.front();
    undo_moves.pop_front();

    grid[c.y][c.x] = c.value;

    QTableWidgetItem* item = ui->Board->item(c.y,c.x);

    redo_moves.emplace_front(c.x,c.y,modifyItem(item,c.value));

    if (!redo_moves.empty()) {
        ui->redoMove->setEnabled(true);
    }
    if (undo_moves.empty()) {
        ui->undoMove->setEnabled(false);
    }
}

// redoes the last move undone
void MainWindow::on_redoMove_clicked()
{
    Cell c = redo_moves.front();
    redo_moves.pop_front();

    grid[c.y][c.x] = c.value;

    QTableWidgetItem* item = ui->Board->item(c.y,c.x);

    undo_moves.emplace_front(c.x,c.y,modifyItem(item,c.value));

    if (redo_moves.empty()) {
        ui->redoMove->setEnabled(false);
    }

    if (!undo_moves.empty()) {
        ui->undoMove->setEnabled(true);
    }
}

// helper function for the above 2, removes repeat code
int MainWindow::modifyItem(QTableWidgetItem *item, int val) {
    int old_value = 0;
    if (item->backgroundColor() == Qt::lightGray) {
        old_value = 0;
    } else if (item->backgroundColor() == Qt::black) {
        old_value = -1;
    } else if (item->backgroundColor() == Qt::white) {
        old_value = -2;
    }

    if (val == 0) {
        item->setBackground(Qt::lightGray);
    } else if (val == -1) {
        item->setBackground(Qt::black);
    } else if (val == -2) {
        item->setBackground(Qt::white);
    }
    return old_value;
}

// prints the grid for debugging purposes into console
void MainWindow::printGrid() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

// quits the application
void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}
