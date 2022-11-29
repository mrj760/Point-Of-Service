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
#include <backbone.h>
#include <testmodule.h>
#include <module.h>

int main(int argc, char *argv[])
{
    Backbone bone = Backbone();
//Testing the backbone
    TestMod test = TestMod();
    bone.addModule(test);
    std::cout << "Test module's ID: " + std::to_string(bone.getIDFromList("TST"));

    QApplication a(argc, argv);

    a.setStyle("fusion");

    MainWindow w;
    w.show();

    dbmanager* dbmgr = new dbmanager("QPSQL","posdb");

    w.setDB(dbmgr);

    return a.exec();
}
