//
// Created by admin on 01.06.2023.
//

#ifndef GAME_SOKOBAN_PIXMAPCREATIONBUTTON_H
#define GAME_SOKOBAN_PIXMAPCREATIONBUTTON_H

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPen>
#include <QColor>
#include <QGraphicsItem>
#include <QResizeEvent>
#include <QGraphicsPixmapItem>

class ButtonCreationPixmapItem : public QObject, public QGraphicsPixmapItem {
Q_OBJECT

public:
    explicit ButtonCreationPixmapItem(int row, int col, const QPixmap &pixmap, QGraphicsItem *parent = nullptr)
            : QGraphicsPixmapItem(pixmap, parent), row_(row),
              col_(col) {}

signals:

    void clicked(int row, int col);
    void unClicked(int row, int col);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int row_;
    int col_;
};


#endif //GAME_SOKOBAN_PIXMAPCREATIONBUTTON_H
