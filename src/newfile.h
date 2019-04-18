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

    uint getRow();
    uint getCol();

private:
    Ui::NewFile *ui;
};

#endif // NEWFILE_H
