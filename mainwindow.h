#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlRecord>
#include "qsqlquery.h"
#include <QMessageBox>
#include <QSqlError>
#include <dbmanager.h>

typedef QSqlQuery Query;
typedef QSqlTableModel TableModel;
typedef QSqlDatabase Database;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE




class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setDB(dbmanager*);
    void setTableModel(const QString&);


private slots:
    void on_items_clicked();
    void on_customers_clicked();

    void on_save_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_transactions_clicked();

    void on_registers_clicked();

private:
    dbmanager *dbmgr;
    TableModel *tmodel;
    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_H
