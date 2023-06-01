//
// Created by admin on 31.05.2023.
//

#include "Level.h"
#include <QWidget>
#include "Controller.h"
#include "MatrixTableView.h"
#include <QGridLayout>
#include <QTimer>
#include <QRandomGenerator>
#include <QtConcurrent>

Level::Level(QWidget *parent, int id) : QWidget(parent) {
    controller_ = new Controller();
    int len = controller_->getMaxId();
    if (id == -1) {
        level_ = (QRandomGenerator::global()->bounded(len) + 1);
    } else {
        level_ = id;
    }

    controller_ = new Controller(level_);

    resize(500, 700);
    QGridLayout *layout = new QGridLayout(this);

    view_ = new MatrixView(this);
    view_->setMatrix(controller_->getCurrentMatrix());

    ButtonPixmapItem *solveButtonItem = view_->getSolveButton();
    ButtonPixmapItem *resetButtonItem = view_->getResetButton();
    ButtonPixmapItem *returnButtonItem = view_->getReturnButton();

    layout->addWidget(view_, 0, 0);
    connect(solveButtonItem, &ButtonPixmapItem::clicked, this, &Level::showSolution);
    connect(resetButtonItem, &ButtonPixmapItem::clicked, this, &Level::resetLevel);
    connect(returnButtonItem, &ButtonPixmapItem::clicked, this, &Level::goToMenuSlot);

}

void Level::keyPressEvent(QKeyEvent *event) {

    if (solving_) {
        return;
    }

    int key = event->key();
    switch (key) {
        case Qt::Key_W:
            steps_++;
            controller_->getNextPuzzle('u');
            break;
        case Qt::Key_S:
            steps_++;
            controller_->getNextPuzzle('d');
            break;
        case Qt::Key_A:
            steps_++;
            controller_->getNextPuzzle('l');
            break;
        case Qt::Key_D:
            steps_++;
            controller_->getNextPuzzle('r');
            break;
        default:
            break;
    }
    if (controller_->isSolved()) {
        view_->setFinish();
        solving_ = true;
    }
    view_->setMatrix(controller_->getCurrentMatrix());

    QWidget::keyPressEvent(event);
}

void Level::showSolution() {
    if (solving_) {
        return;
    }
    solving_ = true;
    std::string text = controller_->getSolution();

    int currentIndex = 0;

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() mutable {
        if (currentIndex < text.size()) {
            controller_->getNextPuzzle(text[currentIndex]);
            view_->setMatrix(controller_->getCurrentMatrix());
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
    if (solving_) {
        return;
    }
    delete controller_;

    controller_ = new Controller(level_);

    view_->setMatrix(controller_->getCurrentMatrix());
}

void Level::goToMenuSlot() {
    emit goToMenu();
}
