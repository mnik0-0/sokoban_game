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

    QPixmap backgroundImage(":img/flor");
    scene_->setBackgroundBrush(QBrush(backgroundImage));

    reset_->setZValue(2.0);
}

void MatrixView::setMatrix(const std::vector<std::vector<char>> &matrix) {
    matrix_ = matrix;
    map_.resize(matrix_.size(), QList<QPair<QGraphicsItem *, char>>(matrix_[0].size(), {nullptr, 'n'}));
    updateScene();
}

void MatrixView::resizeEvent(QResizeEvent *event) {
    setSceneRect(QRectF(QPointF(0, 0), event->size()));
    QGraphicsView::resizeEvent(event);
    updateScene();
}


void MatrixView::updateScene() {

    if (matrix_.empty())
        return;

    const int numRows = matrix_.size();
    const int numCols = matrix_[0].size();

    const qreal squareSize = qMin(viewport()->width() / numCols, viewport()->height() / numRows);

    const qreal xOffset = (viewport()->width() - (squareSize * numCols)) / 2;
    const qreal yOffset = (viewport()->height() - (squareSize * numRows)) / 2;

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {

            if (map_[row][col].first == nullptr) {
                if (matrix_[row][col] == ' ') {
                    continue;
                } else {
                    const QPixmap pixmap(getFileName(matrix_[row][col]));
                    QGraphicsPixmapItem *pixmapItem = scene_->addPixmap(pixmap.scaled(squareSize, squareSize));
                    map_[row][col] = {pixmapItem, matrix_[row][col]};
                    pixmapItem->setPos(xOffset + col * squareSize, yOffset + (row) * squareSize);
                    continue;
                }
            }

            if (map_[row][col].second != matrix_[row][col]) {
                const QPixmap pixmap(getFileName(matrix_[row][col]));
                QGraphicsPixmapItem *pixmapItem = scene_->addPixmap(pixmap.scaled(squareSize, squareSize));
                map_[row][col] = {pixmapItem, matrix_[row][col]};
                pixmapItem->setPos(xOffset + col * squareSize, yOffset + (row) * squareSize);
                continue;
            }

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
