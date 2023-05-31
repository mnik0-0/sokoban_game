//
// Created by admin on 31.05.2023.
//

#include "Level.h"
#include <QWidget>
#include "Controller.h"
#include "MatrixTableView.h"
#include <QGridLayout>
#include <QTimer>

Level::Level(QWidget *parent) : QWidget(parent) {
    controller_ = new Controller();

    resize(500, 700);
//    QWidget *centralWidget = new QWidget(this);
    QGridLayout *layout = new QGridLayout(this);
//    setCentralWidget(centralWidget);

    view_ = new MatrixView(this);
//
    view_->setMatrix(controller_->get_current_matrix());

    ButtonPixmapItem *solveButtonItem = view_->getSolveButton();
    ButtonPixmapItem *resetButtonItem = view_->getResetButton();
    ButtonPixmapItem *returnButtonItem = view_->getReturnButton();

    layout->addWidget(view_, 0, 0);
    connect(solveButtonItem, &ButtonPixmapItem::clicked, this, &Level::showSolution);
    connect(resetButtonItem, &ButtonPixmapItem::clicked, this, &Level::resetLevel);
    connect(returnButtonItem, &ButtonPixmapItem::clicked, this, &Level::goToMenuSlot);

    showFullScreen();
}

void Level::keyPressEvent(QKeyEvent *event) {

    if (solving_ || solved_) {
        return;
    }

    int key = event->key();
    switch (key) {
        case Qt::Key_W:
            steps_++;
            controller_->get_next_puzzle('u');
            break;
        case Qt::Key_S:
            steps_++;
            controller_->get_next_puzzle('d');
            break;
        case Qt::Key_A:
            steps_++;
            controller_->get_next_puzzle('l');
            break;
        case Qt::Key_D:
            steps_++;
            controller_->get_next_puzzle('r');
            break;
        default:
            break;
    }
    view_->setMatrix(controller_->get_current_matrix());

    solved_ = controller_->isSolved();

    if (solved_) {
        emit 
    }

    QWidget::keyPressEvent(event);
}

void Level::showSolution() {
    if (solving_ || solved_) {
        return;
    }
    solving_ = true;
    std::string text = controller_->get_solution();

    int currentIndex = 0;

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() mutable {
        if (currentIndex < text.size()) {
            controller_->get_next_puzzle(text[currentIndex]);
            view_->setMatrix(controller_->get_current_matrix());
            currentIndex += 2;
        } else {
            timer->stop();
            timer->deleteLater();
            solving_ = false;
        }
    });
    timer->start(200);


}

void Level::resetLevel() {
    if (solving_ || solved_) {
        return;
    }
    delete controller_;

    controller_ = new Controller();

    view_->setMatrix(controller_->get_current_matrix());
}

void Level::goToMenuSlot() {
    emit goToMenu();
}
