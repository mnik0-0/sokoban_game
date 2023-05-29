
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
#include <QThread>
#include "MatrixTableView.h"
#include "Controller.h"
#include <QTimer>
#include "SolveButton.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    controller_ = new Controller();

    resize(500, 700);
    QWidget *centralWidget = new QWidget(this);
    QGridLayout *layout = new QGridLayout(centralWidget);
    setCentralWidget(centralWidget);

    view_ = new MatrixView(this);

    view_->setMatrix(controller_->get_current_matrix());

    ButtonPixmapItem * solveButtonItem = view_->getSolveButton();
    ButtonPixmapItem * resetButtonItem = view_->getResetButton();

    layout->addWidget(view_, 0, 0);
    connect(solveButtonItem, &ButtonPixmapItem::clicked, this, &MainWindow::showSolution);
    connect(resetButtonItem, &ButtonPixmapItem::clicked, this, &MainWindow::resetLevel);

//    showFullScreen();
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

void MainWindow::showSolution() {

    std::string text = controller_->get_solution();
    int currentIndex = 0;

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() mutable {
        if (currentIndex < text.size()) {
            controller_->get_next_puzzle(text[currentIndex]);
            view_->setMatrix(controller_->get_current_matrix());
            currentIndex += 2;
        } else {
            timer->stop();
            timer->deleteLater();
        }
    });
    timer->start(200);
    
}

void MainWindow::resetLevel() {
    delete controller_;

    controller_ = new Controller();

    view_->setMatrix(controller_->get_current_matrix());
}


