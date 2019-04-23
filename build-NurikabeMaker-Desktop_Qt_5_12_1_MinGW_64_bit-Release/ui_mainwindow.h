/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoad;
    QAction *actionExit;
    QAction *actionNew;
    QAction *actionSave;
    QAction *actionCreate;
    QAction *actionSolve;
    QAction *actionView;
    QAction *saveState_1;
    QAction *saveState_2;
    QAction *saveState_3;
    QAction *loadState_1;
    QAction *loadState_2;
    QAction *loadState_3;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *Board;
    QLabel *console;
    QVBoxLayout *verticalLayout;
    QLabel *statusView;
    QPushButton *solvePuzzle;
    QPushButton *generatePuzzle;
    QPushButton *checkPuzzle;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *undoMove;
    QPushButton *redoMove;
    QSpacerItem *verticalSpacer_2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuStates;
    QMenu *menuLoad;
    QMenu *menuSave;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(564, 390);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/assets/icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionLoad = new QAction(MainWindow);
        actionLoad->setObjectName(QString::fromUtf8("actionLoad"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/assets/load_file.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoad->setIcon(icon1);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/assets/exit_app.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon2);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icon/assets/new_file.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon3);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icon/assets/save_file.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon4);
        actionCreate = new QAction(MainWindow);
        actionCreate->setObjectName(QString::fromUtf8("actionCreate"));
        actionSolve = new QAction(MainWindow);
        actionSolve->setObjectName(QString::fromUtf8("actionSolve"));
        actionView = new QAction(MainWindow);
        actionView->setObjectName(QString::fromUtf8("actionView"));
        saveState_1 = new QAction(MainWindow);
        saveState_1->setObjectName(QString::fromUtf8("saveState_1"));
        saveState_1->setIcon(icon4);
        saveState_2 = new QAction(MainWindow);
        saveState_2->setObjectName(QString::fromUtf8("saveState_2"));
        saveState_2->setIcon(icon4);
        saveState_3 = new QAction(MainWindow);
        saveState_3->setObjectName(QString::fromUtf8("saveState_3"));
        saveState_3->setIcon(icon4);
        loadState_1 = new QAction(MainWindow);
        loadState_1->setObjectName(QString::fromUtf8("loadState_1"));
        loadState_1->setEnabled(false);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icon/assets/invalid.svg"), QSize(), QIcon::Normal, QIcon::Off);
        loadState_1->setIcon(icon5);
        loadState_2 = new QAction(MainWindow);
        loadState_2->setObjectName(QString::fromUtf8("loadState_2"));
        loadState_2->setEnabled(false);
        loadState_2->setIcon(icon5);
        loadState_3 = new QAction(MainWindow);
        loadState_3->setObjectName(QString::fromUtf8("loadState_3"));
        loadState_3->setEnabled(false);
        loadState_3->setIcon(icon5);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        Board = new QTableWidget(centralWidget);
        Board->setObjectName(QString::fromUtf8("Board"));

        verticalLayout_2->addWidget(Board);

        console = new QLabel(centralWidget);
        console->setObjectName(QString::fromUtf8("console"));

        verticalLayout_2->addWidget(console);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        statusView = new QLabel(centralWidget);
        statusView->setObjectName(QString::fromUtf8("statusView"));
        QFont font;
        font.setFamily(QString::fromUtf8("Trebuchet MS"));
        font.setBold(true);
        font.setWeight(75);
        font.setKerning(true);
        statusView->setFont(font);
        statusView->setAutoFillBackground(false);
        statusView->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(statusView);

        solvePuzzle = new QPushButton(centralWidget);
        solvePuzzle->setObjectName(QString::fromUtf8("solvePuzzle"));

        verticalLayout->addWidget(solvePuzzle);

        generatePuzzle = new QPushButton(centralWidget);
        generatePuzzle->setObjectName(QString::fromUtf8("generatePuzzle"));

        verticalLayout->addWidget(generatePuzzle);

        checkPuzzle = new QPushButton(centralWidget);
        checkPuzzle->setObjectName(QString::fromUtf8("checkPuzzle"));

        verticalLayout->addWidget(checkPuzzle);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        undoMove = new QPushButton(centralWidget);
        undoMove->setObjectName(QString::fromUtf8("undoMove"));
        undoMove->setEnabled(false);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(undoMove->sizePolicy().hasHeightForWidth());
        undoMove->setSizePolicy(sizePolicy);
        undoMove->setMaximumSize(QSize(36, 16777215));

        horizontalLayout_2->addWidget(undoMove);

        redoMove = new QPushButton(centralWidget);
        redoMove->setObjectName(QString::fromUtf8("redoMove"));
        redoMove->setEnabled(false);
        sizePolicy.setHeightForWidth(redoMove->sizePolicy().hasHeightForWidth());
        redoMove->setSizePolicy(sizePolicy);
        redoMove->setMaximumSize(QSize(36, 16777215));

        horizontalLayout_2->addWidget(redoMove);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 17, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 564, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuStates = new QMenu(menuBar);
        menuStates->setObjectName(QString::fromUtf8("menuStates"));
        menuLoad = new QMenu(menuStates);
        menuLoad->setObjectName(QString::fromUtf8("menuLoad"));
        menuSave = new QMenu(menuStates);
        menuSave->setObjectName(QString::fromUtf8("menuSave"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuStates->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionLoad);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionExit);
        menuEdit->addAction(actionCreate);
        menuEdit->addAction(actionSolve);
        menuEdit->addAction(actionView);
        menuStates->addAction(menuSave->menuAction());
        menuStates->addAction(menuLoad->menuAction());
        menuLoad->addAction(loadState_1);
        menuLoad->addAction(loadState_2);
        menuLoad->addAction(loadState_3);
        menuSave->addAction(saveState_1);
        menuSave->addAction(saveState_2);
        menuSave->addAction(saveState_3);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Nurikabe Maker", nullptr));
        actionLoad->setText(QApplication::translate("MainWindow", "Load", nullptr));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
        actionNew->setText(QApplication::translate("MainWindow", "New", nullptr));
        actionSave->setText(QApplication::translate("MainWindow", "Save", nullptr));
        actionCreate->setText(QApplication::translate("MainWindow", "Create", nullptr));
        actionSolve->setText(QApplication::translate("MainWindow", "Solve", nullptr));
        actionView->setText(QApplication::translate("MainWindow", "View", nullptr));
        saveState_1->setText(QApplication::translate("MainWindow", "State 1", nullptr));
        saveState_2->setText(QApplication::translate("MainWindow", "State 2", nullptr));
        saveState_3->setText(QApplication::translate("MainWindow", "State 3", nullptr));
        loadState_1->setText(QApplication::translate("MainWindow", "State 1", nullptr));
        loadState_2->setText(QApplication::translate("MainWindow", "State 2", nullptr));
        loadState_3->setText(QApplication::translate("MainWindow", "State 3", nullptr));
        console->setText(QString());
        statusView->setText(QApplication::translate("MainWindow", "CREATE", nullptr));
        solvePuzzle->setText(QApplication::translate("MainWindow", "Solve", nullptr));
        generatePuzzle->setText(QApplication::translate("MainWindow", "Generate", nullptr));
        checkPuzzle->setText(QApplication::translate("MainWindow", "Check", nullptr));
        undoMove->setText(QApplication::translate("MainWindow", "Undo", nullptr));
        redoMove->setText(QApplication::translate("MainWindow", "Redo", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Change Mode", nullptr));
        menuStates->setTitle(QApplication::translate("MainWindow", "States", nullptr));
        menuLoad->setTitle(QApplication::translate("MainWindow", "Load", nullptr));
        menuSave->setTitle(QApplication::translate("MainWindow", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
