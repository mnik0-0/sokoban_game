//
// Created by admin on 28.05.2023.
//

#include "SolveButton.h"

void ButtonPixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event)  {
    emit clicked();
}
