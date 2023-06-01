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

void Model::saveLevel(const std::vector<std::vector<char>> &vector) {

    QStringList list;
    for (int i = 0; i < vector.size(); ++i) {
        std::string tmp;
        for (int j = 0; j < vector[0].size(); ++j) {
            tmp += vector[i][j];
        }
        list.push_back(QString::fromStdString(tmp));
    }

    QFile file(":levels/levels.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "ERROR READING";
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData);
    if (jsonDocument.isNull()) {
        qDebug() << "ERROR DUMP";
        return;
    }

    QJsonObject jsonObject = jsonDocument.object();

    int len = jsonObject["len"].toInt();

    QJsonObject newLevel;
    QJsonArray jsonArray;
    for (const QString& str : list) {
        jsonArray.append(str);
    }
    newLevel["level"] = jsonArray;

    QString levelKey = QString::number(len + 1);
    QJsonObject levelsObject = jsonObject["levels"].toObject();
    levelsObject.insert(levelKey, newLevel);
    jsonObject["levels"] = levelsObject;
    jsonObject["len"] = len + 1;

    jsonDocument = QJsonDocument(jsonObject);

    QFile file2("C:\\Users\\admin\\Desktop\\sokoban\\sokoban_game\\levels\\levels.json");
    if (!file2.open(QIODevice::WriteOnly)) {
        qDebug() << "ERROR WRITING" << file2.errorString();
        return;
    }

    file2.write(jsonDocument.toJson());
    file2.close();


}
