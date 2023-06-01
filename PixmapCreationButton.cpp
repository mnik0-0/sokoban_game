//
// Created by admin on 01.06.2023.
//

#include "PixmapCreationButton.h"
#include <QGraphicsSceneMouseEvent>

void ButtonCreationPixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit clicked(row_, col_);
        return;
    }
    if (event->button() == Qt::RightButton) {
        emit unClicked(row_, col_);
        return;
    }

}
