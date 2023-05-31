//
// Created by admin on 31.05.2023.
//

#include "Menu.h"
#include "PixmapButton.h"

MenuWidget::MenuWidget(QWidget *parent) : QGraphicsView(parent) {

    scene_ = new QGraphicsScene(this);
    setScene(scene_);


    QPixmap backgroundImage(":img/flor");
    scene_->setBackgroundBrush(QBrush(backgroundImage));

    play_ = new ButtonPixmapItem(QPixmap(":img/play.png"));

    sound_ = new ButtonPixmapItem(QPixmap(":img/sound.png"));

    exit_ = new ButtonPixmapItem(QPixmap(":img/exit.png"));


    scene_->addItem(play_);

    scene_->addItem(sound_);

    scene_->addItem(exit_);
    updateScene();

    connect(play_, &ButtonPixmapItem::clicked, this, &MenuWidget::onPlayClicked);
}

void MenuWidget::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    setSceneRect(QRectF(QPointF(0, 0), event->size()));

    updateScene();
}

void MenuWidget::updateScene() {


    int buttonWidth = std::min(width() / 1.5, 500.0);
    int buttonHeight = std::min(height() / 4, 200);
    int spacing = buttonHeight / 4;

    int sceneWidth = width();
    int sceneHeight = height();

    int totalHeight = buttonHeight * 3 + spacing * 2;

    int buttonX = (sceneWidth - buttonWidth) / 2;
    int buttonY = (sceneHeight - totalHeight) / 2;

    play_->setPos(buttonX, buttonY);

    sound_->setPos(buttonX, buttonY + buttonHeight + spacing);

    exit_->setPos(buttonX, buttonY + (buttonHeight + spacing) * 2);


    play_->setPixmap(QPixmap(":img/play.png").scaled(buttonWidth, buttonHeight));
    sound_->setPixmap(QPixmap(":img/sound.png").scaled(buttonWidth, buttonHeight));
    exit_->setPixmap(QPixmap(":img/exit.png").scaled(buttonWidth, buttonHeight));
}

void MenuWidget::onPlayClicked() {
    emit goToLevel();
}
