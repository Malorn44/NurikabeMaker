#include "newfile.h"
#include "ui_newfile.h"

// constructor for NewFile
NewFile::NewFile(QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint),
    ui(new Ui::NewFile)
{
    ui->setupUi(this);

    // only lets user type in numbers into the lineEdits
    ui->lineEdit->setValidator(new QRegExpValidator(QRegExp("[1-9][0-9]+")));
    ui->lineEdit_2->setValidator(new QRegExpValidator(QRegExp("[1-9][0-9]+")));
}

// destructor for NewFile
NewFile::~NewFile()
{
    delete ui;
}

// returns the value stored in lineEdit->text (or -1 if invalid)
int NewFile::getRow() {
    if (ui->lineEdit->text().isEmpty()) return -1;
    return stoul(ui->lineEdit->text().toStdString());
}

// returns the value stored in lineEdit_2->text (or -1 if invalid)
int NewFile::getCol() {
    if (ui->lineEdit_2->text().isEmpty()) return -1;
    return stoul(ui->lineEdit_2->text().toStdString());
}
