//
// Created by Nikita on 21.05.2023.
//

#ifndef GAME_SOKOBAN_MAINWINDOW_H
#define GAME_SOKOBAN_MAINWINDOW_H


#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include "Controller.h"
#include "MatrixTableView.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Controller* controller_;
    MatrixView* view_;
};

QCursor getWhiteCursor();

#endif //GAME_SOKOBAN_MAINWINDOW_H
