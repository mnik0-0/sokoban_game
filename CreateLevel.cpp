//
// Created by admin on 31.05.2023.
//

#include "CreateLevel.h"
#include <QGridLayout>
#include <QRadioButton>
#include <QLineEdit>

CreateLevel::CreateLevel(QWidget *parent) : QWidget(parent) {

    QGridLayout *layout = new QGridLayout(this);

    // Создание радиокнопок
    QRadioButton *radioButton1 = new QRadioButton("Опция 1", this);
    QRadioButton *radioButton2 = new QRadioButton("Опция 2", this);
    QRadioButton *radioButton3 = new QRadioButton("Опция 3", this);
    QRadioButton *radioButton4 = new QRadioButton("Опция 4", this);

    // Создание полей для ввода чисел
    QLineEdit *lineEdit1 = new QLineEdit(this);
    QLineEdit *lineEdit2 = new QLineEdit(this);

    // Создание QGraphicsView и QGraphicsScene
    QGraphicsScene *scene = new QGraphicsScene(this);
    QGraphicsView *view = new QGraphicsView(scene, this);

    // Добавление элементов в сетку
    layout->addWidget(radioButton1, 0, 0);
    layout->addWidget(radioButton2, 0, 1);
    layout->addWidget(radioButton3, 0, 2);
    layout->addWidget(lineEdit1, 1, 0);
    layout->addWidget(lineEdit2, 1, 1);
    layout->addWidget(view, 2, 0, 1, 3);
}
