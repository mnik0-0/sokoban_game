//
// Created by admin on 31.05.2023.
//

#ifndef GAME_SOKOBAN_CREATELEVEL_H
#define GAME_SOKOBAN_CREATELEVEL_H

#include "Controller.h"
#include "MatrixTableCreationView.h"
#include <QLineEdit>
#include <QObject>
#include <QKeyEvent>
#include <QLabel>

class CreateLevel : public QWidget {
Q_OBJECT

public:
    explicit CreateLevel(QWidget *parent = nullptr);

private:
    void keyPressEvent(QKeyEvent *event) override;

signals:

    void goToMenu();

    void newItem();

private slots:

    void updateValue(int row, int col);

    void deleteValue(int row, int col);

    void resizeMatrix();

    void send();

    void goToMenuSlot();



private:
    QLineEdit *rows_;
    QLineEdit *cols_;
    Controller *controller_;
    MatrixCreationView *view_;
    QLabel* errors_;
    char value_ = '#';
};

#endif //GAME_SOKOBAN_CREATELEVEL_H
