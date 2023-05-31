//
// Created by admin on 31.05.2023.
//

#ifndef GAME_SOKOBAN_CREATELEVEL_H
#define GAME_SOKOBAN_CREATELEVEL_H

#include "Controller.h"
#include "MatrixTableView.h"

#include <QObject>
class CreateLevel: public QWidget {
Q_OBJECT
public:
    explicit CreateLevel(QWidget *parent = nullptr);

signals:
//    void goToMenu();

private slots:

//    void goToMenuSlot();

private:
    Controller* controller_{};
    MatrixView* view_{};
    bool solving_ = false;
};

#endif //GAME_SOKOBAN_CREATELEVEL_H
