//
// Created by Nikita on 21.05.2023.
//
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPen>
#include <QColor>
#include <QGraphicsItem>
#include <QResizeEvent>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include "MatrixTableView.h"
#include "PixmapButton.h"
#include <iostream>


MatrixView::MatrixView(QWidget *parent, bool resized, bool buttons, bool clickable, int id) : QGraphicsView(parent), resized_(resized), buttons_(buttons), clickable_(clickable), id_(id) {

    setAlignment(Qt::AlignCenter);

    scene_ = new QGraphicsScene(this);
    setScene(scene_);

    if (buttons) {
        const QPixmap solvePixmap(":img/solve.png");
        solve_ = new ButtonPixmapItem(solvePixmap.scaled(60, 60));
        scene_->addItem(solve_);

        const QPixmap resetPixmap(":img/reset.png");
        reset_ = new ButtonPixmapItem(resetPixmap.scaled(60, 60));
        scene_->addItem(reset_);

        const QPixmap returnPixmap(":img/home.png");
        return_ = new ButtonPixmapItem(returnPixmap.scaled(60, 60));
        scene_->addItem(return_);



        solve_->setZValue(2.0);
        reset_->setZValue(2.0);
        return_->setZValue(2.0);
    }


    QPixmap backgroundImage(":img/flor.png");
    scene_->setBackgroundBrush(QBrush(backgroundImage));
}

void MatrixView::setMatrix(const std::vector<std::vector<char>> &matrix) {
    matrix_ = matrix;
    updateScene();
}

void MatrixView::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    if (!resized_) {
        if (normalSize_) {
            return;
        }
        normalSize_ = true;
    }
    setSceneRect(QRectF(QPointF(0, 0), event->size()));
    updateScene();
}


void MatrixView::updateScene() {

    for (QGraphicsItem *item: map_) {
        scene_->removeItem(item);
        delete item;
    }
    map_.clear();

    if (matrix_.empty())
        return;

    const int numRows = matrix_.size();
    const int numCols = matrix_[0].size();

    const qreal squareSize = qMin(viewport()->width() / numCols, viewport()->height() / numRows);

    const qreal xOffset = (viewport()->width() - (squareSize * numCols)) / 2;
    const qreal yOffset = (viewport()->height() - (squareSize * numRows)) / 2;

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            if (matrix_[row][col] == ' ') {
                continue;
            }
            const QPixmap pixmap(getFileName(matrix_[row][col]));

            QGraphicsPixmapItem *pixmapItem = scene_->addPixmap(pixmap.scaled(squareSize, squareSize));
            pixmapItem->setPos(xOffset + col * squareSize, yOffset + (row) * squareSize);
            map_.push_back(pixmapItem);
        }
    }
    if (buttons_) {
        if (solved_) {
            const QPixmap pixmap(":img/win.png");
            int size = std::min(viewport()->height(), viewport()->width()) / 2;
            QGraphicsPixmapItem *pixmapItem = scene_->addPixmap(pixmap.scaled(size, size));

            pixmapItem->setPos((viewport()->width() - size) / 2, (viewport()->height() - size) / 2);
            map_.push_back(pixmapItem);
        }

        solve_->setPos(0, 0);
        reset_->setPos(viewport()->width() - 60, 0);
        return_->setPos(viewport()->width() - 60, viewport()->height() - 60);
    }

}

QString MatrixView::getFileName(char value) {
    switch (value) {

        case '#': // стена - черный
            return ":img/wall";

        case '@': // игрок - красный
            return ":img/player";

        case '+': // игрок + гоал - розоватый
            return ":img/goalplayer";

        case '$': // бокс - коричневый
            return ":img/box";

        case '*': // бокс + гоал - зеленый
            return ":img/goalbox";

        case '.': // гоал - зеленый
            return ":img/goal";

        case ' ': // пустота - белый
            return ":img/flor";

    }
    return ":img/flor";
}

ButtonPixmapItem *MatrixView::getSolveButton() {
    return solve_;
}

ButtonPixmapItem *MatrixView::getResetButton() {
    return reset_;
}

ButtonPixmapItem *MatrixView::getReturnButton() {
    return return_;
}

void MatrixView::setFinish() {
    solved_ = true;
    updateScene();
}

void MatrixView::mousePressEvent(QMouseEvent* event) {
    QGraphicsView::mousePressEvent(event);
    if (!clickable_) {
        return;
    }
    emit clicked(id_);
}
