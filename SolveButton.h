//
// Created by admin on 28.05.2023.
//

#ifndef GAME_SOKOBAN_SOLVEBUTTON_H
#define GAME_SOKOBAN_SOLVEBUTTON_H

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPen>
#include <QColor>
#include <QGraphicsItem>
#include <QResizeEvent>
#include <QGraphicsPixmapItem>

class ButtonPixmapItem : public QObject, public QGraphicsPixmapItem {
Q_OBJECT

public:
    explicit ButtonPixmapItem(const QPixmap &pixmap, QGraphicsItem *parent = nullptr)
            : QGraphicsPixmapItem(pixmap, parent) {}

signals:
    void clicked();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif //GAME_SOKOBAN_SOLVEBUTTON_H
