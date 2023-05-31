//
// Created by Nikita on 22.05.2023.
//

#include "Model.h"
#include <fstream>
#include <iostream>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QRandomGenerator>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

std::vector<std::vector<char>> Model::levelFromFile(int idLevel) {
//    QString s = ":levels/level" + QString::number(QRandomGenerator::global()->bounded(6) + 1);
//    QFile file(s);
//    file.open(QIODevice::ReadOnly|QIODevice::Text);


    QFile file(":levels/levels.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Не удалось открыть файл JSON для чтения";
    }
    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);

    if (jsonDoc.isNull()) {
        qWarning() << "Ошибка разбора JSON-документа";
    }

    if (!jsonDoc.isObject()) {
        qWarning() << "Некорректный формат JSON-документа";
    }

    QJsonObject jsonObject = jsonDoc.object();
    QString id;
    if (idLevel == -1) {
        int len = jsonObject["len"].toInt();
        id = QString::number(QRandomGenerator::global()->bounded(len) + 1);
    } else {
        id = QString::number(idLevel);
    }

    QJsonArray level = jsonObject["levels"][id]["level"].toArray();

    std::vector<std::vector<char>> res;
    std::string line;
    for (const QJsonValue &value: level) {
        QString s;

        s = value.toString();

        std::vector<char> tmp;
        line = s.toStdString();
        for (int i = 0; i < line.size(); i++) {
            tmp.push_back(line[i]);
        }

        res.push_back(tmp);
    }
    return res;
}

int Model::getMaxId() {
    QFile file(":levels/levels.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Не удалось открыть файл JSON для чтения";
    }
    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);

    if (jsonDoc.isNull()) {
        qWarning() << "Ошибка разбора JSON-документа";
    }

    if (!jsonDoc.isObject()) {
        qWarning() << "Некорректный формат JSON-документа";
    }

    QJsonObject jsonObject = jsonDoc.object();
    return jsonObject["len"].toInt();
}
