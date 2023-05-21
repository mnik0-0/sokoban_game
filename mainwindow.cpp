
#include "mainwindow.h"
#include "iostream"
#include <QVBoxLayout>
#include <QComboBox>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "MatrixTableView.h"
#include "Controller.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    controller_ = new Controller();


    resize(500, 700);
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);

    view_ = new MatrixView(this);
    std::vector<std::vector<char>> t = controller_->get_current_matrix();

    view_->setMatrix(controller_->get_current_matrix());

    layout->addWidget(view_);

}

MainWindow::~MainWindow() {}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    // Получение кода нажатой клавиши
    int key = event->key();

    std::cout << "click" << std::endl;
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


