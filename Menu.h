//
// Created by admin on 31.05.2023.
//

#ifndef GAME_SOKOBAN_MENU_H
#define GAME_SOKOBAN_MENU_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QResizeEvent>
#include "PixmapButton.h"

class MenuWidget : public QGraphicsView {
Q_OBJECT

public:
    MenuWidget(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;


signals:
    void goToLevel();
    void goToLevelSelector();

private slots:
    void onPlayClicked();
    void onSelectorClicked();

private:
    ButtonPixmapItem *play_;

    ButtonPixmapItem *levels_;

    ButtonPixmapItem *exit_;

    QGraphicsScene *scene_;

    void updateScene();
};


#endif //GAME_SOKOBAN_MENU_H
