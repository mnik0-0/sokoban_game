#include <QApplication>
#include <QMainWindow>
#include <QDebug>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();


//    Controller c = Controller();
//    Puzzle puzzle = c.puzzle_;
//
//    for (int i = 0; i < c.puzzle_.walls.size(); ++i) {
//        for (int j = 0; j < c.puzzle_.walls[0].size(); ++j) {
//            std::cout << c.puzzle_.walls[i][j];
//        }
//        std::cout << std::endl;
//    }
//
//    Solver solver(puzzle);
//    std::cout << solver.Solve();

    return 0;
}