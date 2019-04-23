/********************************************************************************
** Form generated from reading UI file 'newfile.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWFILE_H
#define UI_NEWFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NewFile
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit;
    QLabel *label;
    QLineEdit *lineEdit_2;
    QHBoxLayout *horizontalLayout;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *NewFile)
    {
        if (NewFile->objectName().isEmpty())
            NewFile->setObjectName(QString::fromUtf8("NewFile"));
        NewFile->resize(176, 71);
        NewFile->setMaximumSize(QSize(176, 71));
        verticalLayout = new QVBoxLayout(NewFile);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lineEdit = new QLineEdit(NewFile);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);

        label = new QLabel(NewFile);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        lineEdit_2 = new QLineEdit(NewFile);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        horizontalLayout_2->addWidget(lineEdit_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        buttonBox = new QDialogButtonBox(NewFile);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout->addWidget(buttonBox);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(NewFile);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewFile, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewFile, SLOT(reject()));

        QMetaObject::connectSlotsByName(NewFile);
    } // setupUi

    void retranslateUi(QDialog *NewFile)
    {
        NewFile->setWindowTitle(QApplication::translate("NewFile", "New Puzzle", nullptr));
#ifndef QT_NO_WHATSTHIS
        NewFile->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        lineEdit->setPlaceholderText(QApplication::translate("NewFile", "Rows", nullptr));
        label->setText(QApplication::translate("NewFile", "x", nullptr));
        lineEdit_2->setPlaceholderText(QApplication::translate("NewFile", "Cols", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewFile: public Ui_NewFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWFILE_H
