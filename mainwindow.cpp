
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
    setStyleSheet("background-color: rgb(200, 162, 200)");
    resize(500, 700);
    menuWidget_ = new MenuWidget(this);
    setCentralWidget(menuWidget_);
    connect(menuWidget_, &MenuWidget::goToLevel, this, &MainWindow::showLevel);
    connect(menuWidget_, &MenuWidget::goToLevelSelector, this, &MainWindow::showLevelSelector);
}

MainWindow::~MainWindow() {}

void MainWindow::showLevel() {
    level_ = new Level(this);
    setCentralWidget(level_);
    connect(level_, &Level::goToMenu, this, &MainWindow::showMenu);
}

void MainWindow::showLevelSelector() {
    levelSelector_ = new LevelSelector(this);
    setCentralWidget(levelSelector_);
    connect(levelSelector_, &LevelSelector::goToMenu, this, &MainWindow::showMenu);
    connect(levelSelector_, &LevelSelector::goToLevel, this, &MainWindow::showLevelById);
}

void MainWindow::showMenu() {
    menuWidget_ = new MenuWidget(this);
    setCentralWidget(menuWidget_);
    connect(menuWidget_, &MenuWidget::goToLevel, this, &MainWindow::showLevel);
    connect(menuWidget_, &MenuWidget::goToLevelSelector, this, &MainWindow::showLevelSelector);
}

void MainWindow::showLevelById(int i) {
    qDebug() << i;
    level_ = new Level(this, i);
    setCentralWidget(level_);
    connect(level_, &Level::goToMenu, this, &MainWindow::showMenu);
}
