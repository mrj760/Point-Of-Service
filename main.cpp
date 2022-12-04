// Micah Johnson
// Laijy Loiseau
// Jorge Munoz
// Nam Cuong Tran
// Nathan Ware
// Sydney Corrigan
#include "mainwindow.h"
#include <QApplication>
#include <dbmanager.h>
#include <pos.h>
#include <backbone.h>
#include <testmodule.h>
#include <module.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyle("fusion");

    MainWindow w;
    w.show();

    dbmanager* dbmgr = new dbmanager("QPSQL","mydb", "namcuong757","");

    w.setDB(dbmgr);

    return a.exec();
}
