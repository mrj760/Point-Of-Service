#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>

#include <QSqlTableModel>
typedef QSqlTableModel tablemodel;

#include <QSqlRecord>

#include "qsqlquery.h"
typedef QSqlQuery qry;

#include <QMessageBox>
typedef QMessageBox qmsg;

#include <QSqlError>

typedef QString qstr;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE




class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setDB(QSqlDatabase*);
    void setTableModel(const qstr&);


private slots:
    void on_items_clicked();
    void on_customers_clicked();

    void on_save_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_transactions_clicked();

    void on_registers_clicked();

private:
    QSqlDatabase *db;
    tablemodel *tmodel;
    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_H
