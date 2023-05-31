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
#include "PixmapButton.h"
#include "Menu.h"
#include "Level.h"
#include "CreateLevel.h"

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private slots:
    void showLevel();
    void showMenu();

private:
    MenuWidget* menuWidget_;
    Level* level_;
    CreateLevel* createLevel_;
};

QCursor getWhiteCursor();

