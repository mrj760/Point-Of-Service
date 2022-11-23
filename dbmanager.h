#ifndef DBMANAGER_H
#define DBMANAGER_H


#include <QWidget>
#include <QSqlDatabase>
typedef QSqlDatabase Database;
#include <QSqlQuery>
typedef QSqlQuery Query;
#include <QSqlError>
#include <QMessageBox>
#include <vector>
#include <simplecrypt.h>

typedef QString QString;


class dbmanager
{

    SimpleCrypt crypt;
    Database _db;

public:

    dbmanager(const QString& driver, const QString& path);
    const Database& db = _db; /* db getter */

    bool addItem(const int& qty, const int& cents, QWidget* from=nullptr);
    bool addTransaction(const int& cust_phone=0, const int& total_cents=0, const QString& items="",
                        const QString& payment_type="cash", const int& tender=0, const int& change=0,
                        const int& card_number=0, const int& card_exp=0, const int& card_cvv=0, QWidget* from=nullptr);
    bool addCustomer(const QString& phone, const QString &name, const QString &address, const QString&zip, QWidget* from=nullptr);
    bool addRegister(const int& id, const int& cash=20000, QWidget* from=nullptr);

    bool updateItem(const int& sku);
    bool updateTransaction();
    bool updateCustomer();
    bool updateRegister();

     void displayError(const QString& errorType, const QString& errorText, QWidget* from);
     void displayQueryError(const QString& errorType, QWidget* from, const Query& q);
};

#endif // DBMANAGER_H
