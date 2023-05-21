//
// Created by Nikita on 21.05.2023.
//

#ifndef GAME_SOKOBAN_MATRIXTABLEVIEW_H
#define GAME_SOKOBAN_MATRIXTABLEVIEW_H

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

    QColor getColorForValue(char value);

private:
    std::vector<std::vector<char>> matrix_;
    QGraphicsScene *scene_;
};


#endif //GAME_SOKOBAN_MATRIXTABLEVIEW_H
