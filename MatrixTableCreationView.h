//
// Created by admin on 01.06.2023.
//

#ifndef GAME_SOKOBAN_MATRIXTABLECREATIONVIEW_H
#define GAME_SOKOBAN_MATRIXTABLECREATIONVIEW_H

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPen>
#include <QColor>
#include <QGraphicsItem>
#include "PixmapButton.h"
#include "Controller.h"
#include "PixmapCreationButton.h"

class MatrixCreationView : public QGraphicsView {
Q_OBJECT

public:
    explicit MatrixCreationView(QWidget *parent = nullptr);

    void setMatrix(const std::vector<std::vector<char>> &matrix);

    std::vector<std::vector<char>> getMatrix();


protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void updateScene();

    QString getFileName(char value);

signals:
    void updateValue(int row, int col);
    void deleteValue(int row, int col);

protected slots:
    void updateValueSlot(int row, int col);
    void deleteValueSlot(int row, int col);


private:
    std::vector<std::vector<char>> matrix_;
    QGraphicsScene *scene_;

    QList<ButtonCreationPixmapItem *> map_;


};

#endif //GAME_SOKOBAN_MATRIXTABLECREATIONVIEW_H
