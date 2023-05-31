//
// Created by admin on 31.05.2023.
//

#ifndef GAME_SOKOBAN_LEVELSELECTOR_H
#define GAME_SOKOBAN_LEVELSELECTOR_H

#include "Controller.h"
#include "MatrixTableView.h"

#include <QObject>
class LevelSelector: public QWidget {
Q_OBJECT
public:
    explicit LevelSelector(QWidget *parent = nullptr);

protected:

signals:
    void goToMenu();
    void goToLevel(int id);

private slots:
    void goToLevelSlot(int id);

private:
    Controller* controller_;
};

#endif //GAME_SOKOBAN_LEVELSELECTOR_H
