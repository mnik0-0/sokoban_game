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
#include "MatrixTableView.h"

MatrixView::MatrixView(QWidget *parent) : QGraphicsView(parent) {

    setAlignment(Qt::AlignCenter);

    scene_ = new QGraphicsScene(this);
    setScene(scene_);

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
    scene_->clear();

    if (matrix_.empty())
        return;

    const int numRows = matrix_.size();
    const int numCols = matrix_[0].size();

    const qreal squareSize = qMin(viewport()->width() / numCols, viewport()->height() / numRows);

    const qreal xOffset = (viewport()->width() - (squareSize * numCols)) / 2;
    const qreal yOffset = (viewport()->height() - (squareSize * numRows)) / 2;

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            const char value = matrix_[row][col];
            const QColor color = getColorForValue(value);

            QGraphicsRectItem *rectItem = scene_->addRect(xOffset + col * squareSize, yOffset + row * squareSize,
                                                          squareSize, squareSize);
            rectItem->setBrush(QBrush(color));
        }
    }

}

QColor MatrixView::getColorForValue(char value) {
    switch (value) {

        case '#': // стена - черный
            return QColor(0, 0, 0);

        case '@': // игрок - красный
            return QColor(255, 0, 0);

        case '+': // игрок + гоал - розоватый
            return QColor(255, 165, 122);

        case '$': // бокс - коричневый
            return QColor(128, 64, 48);

        case '*': // бокс + гоал - зеленый
            return QColor(0, 255, 0);

        case '.': // гоал - зеленый
            return QColor(255, 255, 0);

        case ' ': // пустота - белый
            return QColor(255, 255, 255);

    }
    return QColor(0, 255, 255);
}
