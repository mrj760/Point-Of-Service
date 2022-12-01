// Micah Johnson
// Jorge Munoz
// Laijy Loiseau
// Nam Cuong Tran
// Nathan Ware
// Sydney Corrigan
#include "mainwindow.h"
#include <QApplication>
#include <dbmanager.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyle("fusion");

    dbmanager("QPSQL","posdb", "postgres", "grant00--");

    MainWindow w;
    w.show();

    return a.exec();
}
