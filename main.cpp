// Micah Johnson
// Jorge Munoz
// Laijy Loiseau
// Nam Cuong Tran
// Nathan Ware
// Sydney
#include "mainwindow.h"
#include <QApplication>
#include <dbmanager.h>
#include <pos.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyle("fusion");

    MainWindow w;
    w.show();

    dbmanager* dbmgr = new dbmanager("QPSQL","posdb");

    w.setDB(dbmgr);

    return a.exec();
}
