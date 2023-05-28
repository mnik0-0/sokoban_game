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
#include "MatrixTableView.h"
#include "SolveButton.h"


MatrixView::MatrixView(QWidget *parent) : QGraphicsView(parent) {

    setAlignment(Qt::AlignCenter);

    scene_ = new QGraphicsScene(this);
    setScene(scene_);

    const QPixmap sPixmap(":img/solve");
    solve_ = new ButtonPixmapItem(sPixmap.scaled(60, 60));
    scene_->addItem(solve_);

    solve_->setZValue(1.0);

    const QPixmap rPixmap(":img/reset");
    reset_ = new ButtonPixmapItem(rPixmap.scaled(60, 60));
    scene_->addItem(reset_);

    reset_->setZValue(2.0);
}

void MatrixView::setMatrix(const std::vector<std::vector<char>> &matrix) {
    matrix_ = matrix;
    updateScene();
}

void MatrixView::resizeEvent(QResizeEvent *event) {
    setSceneRect(QRectF(QPointF(0, 0), event->size()));
    QGraphicsView::resizeEvent(event);
    updateScene();
}



void MatrixView::updateScene() {
    for (QGraphicsItem *item : map_) {
        scene_->removeItem(item);
        delete item;
    }
    map_.clear();
    QPixmap backgroundImage(":img/flor");
    scene_->setBackgroundBrush(QBrush(backgroundImage));
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

    solve_->setPos(0, 0);
    reset_->setPos(viewport()->width() - 60, 0);

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
