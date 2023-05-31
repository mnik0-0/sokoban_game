//
// Created by admin on 31.05.2023.
//

#ifndef GAME_SOKOBAN_LEVEL_H
#define GAME_SOKOBAN_LEVEL_H

#include "Controller.h"
#include "MatrixTableView.h"

#include <QObject>
class Level: public QWidget {
    Q_OBJECT
public:
    explicit Level(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void goToMenu();

private slots:
    void showSolution();
    void resetLevel();
    void goToMenuSlot();

private:
    Controller* controller_;
    MatrixView* view_;
    bool solving_ = false;
    bool solved_ = false;
    int steps_ = 0;
};

#endif //GAME_SOKOBAN_LEVEL_H
