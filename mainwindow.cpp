
#include "mainwindow.h"
#include "iostream"
#include <QVBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QThread>
#include <QTimer>
#include "Menu.h"
#include "Level.h"
#include "CreateLevel.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    resize(500, 700);
    menuWidget_ = new MenuWidget(this);
    setCentralWidget(menuWidget_);
    connect(menuWidget_, &MenuWidget::goToLevel, this, &MainWindow::showLevel);
//    createLevel_ = new CreateLevel(this);
//    setCentralWidget(createLevel_);


//    QMediaPlayer *player = new QMediaPlayer();
//    player->setMedia(QUrl("qrc:/путь_к_аудиофайлу"));  // Обратите внимание на префикс "qrc:"
//    player->setVolume(50);
//    player->setLoopCount(-1);  // -1 означает зацикливание воспроизведения
//    player->play();
}

MainWindow::~MainWindow() {}

void MainWindow::showLevel() {
    disconnect(menuWidget_, &MenuWidget::goToLevel, this, &MainWindow::showLevel);


    level_ = new Level(this);
    setCentralWidget(level_);
    connect(level_, &Level::goToMenu, this, &MainWindow::showMenu);


}

void MainWindow::showMenu() {
    disconnect(level_, &Level::goToMenu, this, &MainWindow::showMenu);


    menuWidget_ = new MenuWidget(this);
    setCentralWidget(menuWidget_);
    connect(menuWidget_, &MenuWidget::goToLevel, this, &MainWindow::showLevel);
}
