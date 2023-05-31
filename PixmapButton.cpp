//
// Created by admin on 28.05.2023.
//

#include "PixmapButton.h"

void ButtonPixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event)  {
    emit clicked();
}
