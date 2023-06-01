//
// Created by admin on 31.05.2023.
//

#include "Menu.h"
#include "PixmapButton.h"

MenuWidget::MenuWidget(QWidget *parent) : QGraphicsView(parent) {

    scene_ = new QGraphicsScene(this);
    setScene(scene_);


    QPixmap backgroundImage(":img/menu.jpg");
    scene_->setBackgroundBrush(QBrush(backgroundImage));

    play_ = new ButtonPixmapItem(QPixmap(":img/play.png"));

    levels_ = new ButtonPixmapItem(QPixmap(":img/levels.png"));

    create_ = new ButtonPixmapItem(QPixmap(":img/create.png"));


    scene_->addItem(play_);

    scene_->addItem(levels_);

    scene_->addItem(create_);
    updateScene();

    connect(play_, &ButtonPixmapItem::clicked, this, &MenuWidget::onPlayClicked);
    connect(levels_, &ButtonPixmapItem::clicked, this, &MenuWidget::onSelectorClicked);
    connect(create_, &ButtonPixmapItem::clicked, this, &MenuWidget::onCreatorClicked);
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

    levels_->setPos(buttonX, buttonY + buttonHeight + spacing);

    create_->setPos(buttonX, buttonY + (buttonHeight + spacing) * 2);


    play_->setPixmap(QPixmap(":img/play.png").scaled(buttonWidth, buttonHeight));
    levels_->setPixmap(QPixmap(":img/levels.png").scaled(buttonWidth, buttonHeight));
    create_->setPixmap(QPixmap(":img/create.png").scaled(buttonWidth, buttonHeight));
}

void MenuWidget::onPlayClicked() {
    emit goToLevel();
}

void MenuWidget::onSelectorClicked() {
    emit goToLevelSelector();
}

void MenuWidget::onCreatorClicked() {
    emit goToLevelCreator();
}
