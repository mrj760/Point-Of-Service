// Micah Johnson
// Jorge Munoz
// Laijy Loiseau
// Nam Cuong Tran
// Nathan Ware
// Sydney 
#include "mainwindow.h"
#include <QApplication>
#include <dbmanager.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    a.setStyle("fusion");

    MainWindow w;
    w.show();

    dbmanager* dbmgr = new dbmanager("QPSQL","posdb");

    w.setDB(dbmgr);

    dbmgr->addItem(15, 2000, &w);

    dbmgr->addTransaction();

    dbmgr->addTransaction();

    dbmgr->addCustomer("7609122224", "Bill Hicks", "123 Faksa St", "24242", &w);

    dbmgr->addRegister(2, 200, &w);

    return a.exec();
}
