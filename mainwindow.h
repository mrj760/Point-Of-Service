#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QtSql>
#include <dbmanager.h>
#include <itemmanagerview.h>
#include <customermanagerview.h>
#include <transactioneditview.h>
#include <transactionsviewer.h>
#include <POS/UI/Window.hpp>
#include <POS/UI/Screen/Home.hpp>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    //~MainWindow();

    QVBoxLayout *mainLayout;

    TransactionsViewer* transactionsviewer = nullptr;

    void openOrderEditor();
    void openOrdersViewer();

    QPushButton *itemmgrbutton, *custmgrbutton;
    QPushButton *neworderbutton, *allordersbutton;
    ItemManagerView* itemmgr = nullptr;
    CustomerManagerView* custmgr = nullptr;

    void openItemMgr();
    void openCustMgr();
    void openRegisterMgr();

private:
    void setupTitle();
    void setupOrderButtons();
    void setupMgrButtons();
    void setupCloseButton();

    //    TransactionEditView* transactioneditor = nullptr;
    TransactionContainer* internalWindowHolder = nullptr;
    Home* transactioneditor = nullptr;
};



#endif // MAINWINDOW_H
