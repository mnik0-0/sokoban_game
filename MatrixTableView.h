//
// Created by Nikita on 21.05.2023.
//
#pragma once

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPen>
#include <QColor>
#include <QGraphicsItem>
#include "PixmapButton.h"
#include "Controller.h"

class MatrixView : public QGraphicsView {
Q_OBJECT

public:
    MatrixView(QWidget *parent = nullptr, bool resized = true, bool buttons = true, bool clickable = false, int id = -1);

    void setMatrix(const std::vector<std::vector<char>> &matrix);

    void setFinish();

    ButtonPixmapItem* getSolveButton();
    ButtonPixmapItem* getResetButton();
    ButtonPixmapItem* getReturnButton();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    void updateScene();
    QString getFileName(char value);

signals:
    void clicked(int id);

private:
    std::vector<std::vector<char>> matrix_;
    QGraphicsScene *scene_;
    ButtonPixmapItem *solve_;
    ButtonPixmapItem *reset_;
    ButtonPixmapItem *return_;
    QList<QGraphicsItem *> map_;
    bool solved_ = false;
    bool resized_;
    bool normalSize_ = false;
    bool buttons_;
    bool clickable_;
    int id_;

};

