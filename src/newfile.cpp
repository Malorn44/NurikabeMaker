#include "newfile.h"
#include "ui_newfile.h"

#include <iostream>

#include <QRegExpValidator>
#include <QRegExp>

NewFile::NewFile(QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint),
    ui(new Ui::NewFile)
{
    ui->setupUi(this);

    ui->lineEdit->setValidator(new QRegExpValidator(QRegExp("[1-9][0-9]+")));
    ui->lineEdit_2->setValidator(new QRegExpValidator(QRegExp("[1-9][0-9]+")));
}

NewFile::~NewFile()
{
    delete ui;
}

uint NewFile::getRow() {
    return stoul(ui->lineEdit->text().toStdString());
}

uint NewFile::getCol() {
    return stoul(ui->lineEdit_2->text().toStdString());
}
