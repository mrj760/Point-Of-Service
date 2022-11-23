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

//    a.setStyle("fusion");

    MainWindow w;
    w.show();

    dbmanager* dbmgr = new dbmanager("QPSQL","posdb");

    w.setDB(dbmgr);

    dbmgr->addItem(Item());

    dbmgr->addTransaction(Transaction());

    dbmgr->addTransaction(Transaction());

    dbmgr->addCustomer(Customer("7609122224", "Bill Hicks", "123 Faksa St", "24242"));

    dbmgr->addRegister(Register(2, 200));

    return a.exec();
}
