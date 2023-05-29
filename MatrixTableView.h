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
#include "SolveButton.h"
#include "Controller.h"

class MatrixView : public QGraphicsView {
Q_OBJECT

public:
    MatrixView(QWidget *parent = nullptr);

    void setMatrix(const std::vector<std::vector<char>> &matrix);

    ButtonPixmapItem* getSolveButton();
    ButtonPixmapItem* getResetButton();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void updateScene();

    QString getFileName(char value);

private:
    std::vector<std::vector<char>> matrix_;
    QGraphicsScene *scene_;
    ButtonPixmapItem *solve_;
    ButtonPixmapItem *reset_;
    QList<QList<QPair<QGraphicsItem *, char>>> map_;

};

