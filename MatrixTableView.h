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

class MatrixView : public QGraphicsView {
public:
    MatrixView(QWidget *parent = nullptr);

    void setMatrix(const std::vector<std::vector<char>> &matrix);

protected:
    void resizeEvent(QResizeEvent *event) override;
private:
    void updateScene();

    QString getFileName(char value);

private:
    std::vector<std::vector<char>> matrix_;
    QGraphicsScene *scene_;
};

