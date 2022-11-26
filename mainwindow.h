#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlRecord>
#include "qsqlquery.h"
#include <QMessageBox>
#include <QSqlError>
#include <dbmanager.h>
#include <itemaddview.h>
#include <customermanagerview.h>

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

    ItemAddView* itemaddview;
    CustomerManagerView* customerManagerView;


private slots:
    void on_items_clicked();
    void on_customers_clicked();

    void on_save_clicked();

    void on_transactions_clicked();

    void on_registers_clicked();

private:
    dbmanager *dbmgr;
    TableModel *tmodel;
    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_H
