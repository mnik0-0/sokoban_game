//
// Created by admin on 01.06.2023.
//

#include "MatrixTableCreationView.h"
#include "PixmapCreationButton.h"


void MatrixCreationView::setMatrix(const std::vector<std::vector<char>> &matrix) {
    matrix_ = matrix;
    updateScene();
}

MatrixCreationView::MatrixCreationView(QWidget *parent) : QGraphicsView(parent) {
    setAlignment(Qt::AlignCenter);

    scene_ = new QGraphicsScene(this);
    setScene(scene_);

    QPixmap backgroundImage(":img/flor.png");
    scene_->setBackgroundBrush(QBrush(backgroundImage));
}

void MatrixCreationView::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);

    setSceneRect(QRectF(QPointF(0, 0), event->size()));
    updateScene();
}

void MatrixCreationView::updateScene() {

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

            const QPixmap pixmap(getFileName(matrix_[row][col]));

            ButtonCreationPixmapItem *pixmapItem = new ButtonCreationPixmapItem(row, col, pixmap.scaled(squareSize, squareSize));
            scene_->addItem(pixmapItem);
            pixmapItem->setPos(xOffset + col * squareSize, yOffset + (row) * squareSize);

            connect(pixmapItem, &ButtonCreationPixmapItem::clicked, this, &MatrixCreationView::updateValueSlot);
            connect(pixmapItem, &ButtonCreationPixmapItem::unClicked, this, &MatrixCreationView::deleteValueSlot);
            map_.push_back(pixmapItem);
        }
    }

}

QString MatrixCreationView::getFileName(char value) {
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
            return ":img/empty";

    }
    return ":img/flor";
}

void MatrixCreationView::updateValueSlot(int row, int col) {
    emit updateValue(row, col);
}

std::vector<std::vector<char>> MatrixCreationView::getMatrix() {
    return matrix_;
}

void MatrixCreationView::deleteValueSlot(int row, int col) {
    emit deleteValue(row, col);
}
