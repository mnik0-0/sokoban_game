//
// Created by Nikita on 21.05.2023.
//

#pragma once

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QLabel>
#include "Controller.h"
#include "MatrixTableView.h"
#include "SolveButton.h"

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

private slots:
    void showSolution();
    void resetLevel();

private:
    Controller* controller_;
    MatrixView* view_;
};

QCursor getWhiteCursor();

