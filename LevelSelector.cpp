//
// Created by admin on 31.05.2023.
//

#include "LevelSelector.h"
#include "MatrixTableView.h"
#include <QGridLayout>

LevelSelector::LevelSelector(QWidget *parent): QWidget(parent) {
    controller_ = new Controller();
    int len = controller_->getMaxId();


    QGridLayout * layout = new QGridLayout(this);
    for (int i = 1; i < len + 1; ++i) {
        MatrixView * tmp = new MatrixView(this, false, false, true, i);
        tmp->setMatrix(controller_->getPuzzleById(i));
        layout->addWidget(tmp, (i - 1) / 5, (i - 1) % 5);
        connect(tmp, &MatrixView::clicked, this, &LevelSelector::goToLevelSlot);
    }
}

void LevelSelector::goToLevelSlot(int id) {
    emit goToLevel(id);
}
