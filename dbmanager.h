#ifndef DBMANAGER_H
#define DBMANAGER_H


#include <QWidget>
#include <QSqlDatabase>
typedef QSqlDatabase database;
#include <QSqlQuery>
typedef QSqlQuery qry;
#include <QSqlError>
#include <QMessageBox>
typedef QMessageBox qmsg;
#include <vector>
#include <simplecrypt.h>

typedef QString qstr;


class dbmanager
{

    SimpleCrypt crypt;

public:

    dbmanager(const qstr& driver, const qstr& path);
    database db;

    bool addItem(const int& qty, const int& cents, QWidget* from);
    bool addTransaction(const int& cust_phone, const int& total_cents, const qstr& items,
                        const qstr& payment_type, const int& tender, const int& change,
                        const int& card_number, const int& card_exp, const int& card_cvv, QWidget* from);
    bool addCustomer(const int& phone, const qstr& name, const qstr& address, const int& zip, QWidget* from);
    bool addRegister(const int& id, const int& cash, QWidget* from);
     void displayError(const qstr& errorType, QWidget* from, const qry& q);
};

#endif // DBMANAGER_H
