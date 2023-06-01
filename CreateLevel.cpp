//
// Created by admin on 31.05.2023.
//

#include "CreateLevel.h"
#include <QGridLayout>
#include <QRadioButton>
#include <QLineEdit>
#include "MatrixTableCreationView.h"
#include <QPushButton>
#include <QLabel>
#include <QtConcurrent>

CreateLevel::CreateLevel(QWidget *parent) : QWidget(parent) {

    QGridLayout *layout = new QGridLayout(this);

    rows_ = new QLineEdit(this);
    cols_ = new QLineEdit(this);
    rows_->setAlignment(Qt::AlignCenter);
    cols_->setAlignment(Qt::AlignCenter);

    errors_ = new QLabel();
    errors_->setAlignment(Qt::AlignCenter);
    errors_->setText("WALL");

    QPushButton *resetSizeButton = new QPushButton(this);
    resetSizeButton->setText("Reset");

    QPushButton *sendButton = new QPushButton(this);
    sendButton->setText("Save");

    QPushButton *toMenu = new QPushButton(this);
    toMenu->setText("Menu");

    controller_ = new Controller();
    view_ = new MatrixCreationView(this);
    view_->setMatrix({{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}});

    layout->addWidget(rows_, 0, 0);
    layout->addWidget(cols_, 0, 1);
    layout->addWidget(resetSizeButton, 1, 0, 1, 2);
    layout->addWidget(sendButton, 2, 0, 1, 2);
    layout->addWidget(toMenu, 3, 0, 1, 2);
    layout->addWidget(errors_, 4, 0, 1, 2);
    layout->addWidget(view_, 5, 0, 1, 2);

    connect(view_, &MatrixCreationView::updateValue, this, &CreateLevel::updateValue);
    connect(view_, &MatrixCreationView::deleteValue, this, &CreateLevel::deleteValue);

    connect(resetSizeButton, &QPushButton::clicked, this, &CreateLevel::resizeMatrix);
    connect(sendButton, &QPushButton::clicked, this, &CreateLevel::send);
    connect(toMenu, &QPushButton::clicked, this, &CreateLevel::goToMenuSlot);
}

void CreateLevel::updateValue(int row, int col) {
    std::vector<std::vector<char>> matrix = view_->getMatrix();
    if (value_ == '@') {
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[0].size(); ++j) {
                if (matrix[i][j] == '@' || matrix[i][j] == '+') {
                    return;
                }
            }
        }
        if (matrix[row][col] == '.') {
            matrix[row][col] = '+';
            view_->setMatrix(matrix);
            return;
        }
    }
    if (value_ == '$') {
        if (matrix[row][col] == '.') {
            matrix[row][col] = '*';
            view_->setMatrix(matrix);
            return;
        }
    }
    if (value_ == '.') {
        if (matrix[row][col] == '$') {
            matrix[row][col] = '*';
            view_->setMatrix(matrix);
            return;
        }
        if (matrix[row][col] == '@') {
            matrix[row][col] = '+';
            view_->setMatrix(matrix);
            return;
        }
    }

    matrix[row][col] = value_;
    view_->setMatrix(matrix);
}

void CreateLevel::deleteValue(int row, int col) {
    std::vector<std::vector<char>> matrix = view_->getMatrix();
    matrix[row][col] = ' ';
    view_->setMatrix(matrix);
}

void CreateLevel::resizeMatrix() {
    int rows_num = rows_->text().toInt();
    int cols_num = cols_->text().toInt();
    if (!rows_num || !cols_num) {
        return;
    }
    rows_num = std::min(10, rows_num);
    cols_num = std::min(10, cols_num);
    std::vector<std::vector<char>> matrix(rows_num, std::vector<char>(cols_num, ' '));
    view_->setMatrix(matrix);
}

void CreateLevel::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_1:
            value_ = '#';
            errors_->setText("WALL");
            break;
        case Qt::Key_2:
            value_ = '@';
            errors_->setText("PLAYER");
            break;
        case Qt::Key_3:
            value_ = '$';
            errors_->setText("BOX");
            break;
        case Qt::Key_4:
            value_ = '.';
            errors_->setText("GOAL");
            break;
        default:
            break;
    }

    QWidget::keyPressEvent(event);
}

void CreateLevel::send() {
    QString error = controller_->checkValid(view_->getMatrix());
    if (error != "good") {
        errors_->setText(error);
        return;
    }
    controller_->setPuzzle(view_->getMatrix());
    std::string sol = controller_->getSolution();
    if (sol.empty()) {
        errors_->setText("No Solution");
        return;
    }
    errors_->setText("Saving");
    controller_->saveLevel(view_->getMatrix());

}

void CreateLevel::goToMenuSlot() {
    emit goToMenu();
}
