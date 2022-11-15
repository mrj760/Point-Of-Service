// Micah Johnson
// Jorge Munoz
// Laijy Loiseau
// Nam Cuong Tran
// Nathan Ware
// Sydney 
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    int Backbone::modCount = 0;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
