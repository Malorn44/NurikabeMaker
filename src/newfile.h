#ifndef NEWFILE_H
#define NEWFILE_H

#include <QDialog>

namespace Ui {
class NewFile;
}

class NewFile : public QDialog
{
    Q_OBJECT

public:
    explicit NewFile(QWidget *parent = nullptr);
    ~NewFile();

    int getRow();
    int getCol();

private:
    Ui::NewFile *ui;
};

#endif // NEWFILE_H
