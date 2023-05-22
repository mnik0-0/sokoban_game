
#include "mainwindow.h"
#include "iostream"
#include <QVBoxLayout>
#include <QComboBox>
#include <QGraphicsView>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QKeyEvent>
#include <QLabel>
#include "MatrixTableView.h"
#include "Controller.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    controller_ = new Controller();

    QPushButton* solveButton = new QPushButton(this);
    solveButton->setText("Solve");

    resize(500, 700);
    label_ = new QLabel();
    QWidget *centralWidget = new QWidget(this);
    QGridLayout *layout = new QGridLayout(centralWidget);
    setCentralWidget(centralWidget);

    view_ = new MatrixView(this);
    std::vector<std::vector<char>> t = controller_->get_current_matrix();

    view_->setMatrix(controller_->get_current_matrix());

    layout->addWidget(solveButton, 0, 0);
    layout->addWidget(label_, 2, 0);
    layout->addWidget(view_, 3, 0);
    connect(solveButton, &QPushButton::clicked, this, &MainWindow::printSolution);
}

MainWindow::~MainWindow() {}

void MainWindow::keyPressEvent(QKeyEvent *event) {

    int key = event->key();

    switch (key) {
        case Qt::Key_W:
            controller_->get_next_puzzle('u');
            break;
        case Qt::Key_S:
            controller_->get_next_puzzle('d');
            break;
        case Qt::Key_A:
            controller_->get_next_puzzle('l');
            break;
        case Qt::Key_D:
            controller_->get_next_puzzle('r');
            break;
        default:
            break;
    }
    view_->setMatrix(controller_->get_current_matrix());

    QMainWindow::keyPressEvent(event);
}

void MainWindow::printSolution() {
    std::string text = controller_->get_solution();
    label_->setText(QString::fromStdString(text));
}


